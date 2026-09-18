"""Compile the real program and exercise its file-format and scheduling contracts."""
import pathlib
import subprocess
import tempfile
import unittest

ROOT = pathlib.Path(__file__).resolve().parents[1]
SOURCES = ["main.cpp", "customer.cpp", "mechanic.cpp", "person.cpp"]


class SchedulerTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.build = tempfile.TemporaryDirectory()
        cls.binary = pathlib.Path(cls.build.name) / "scheduler"
        subprocess.run(
            ["g++", "-std=c++17", "-Wall", "-Wextra", "-Wpedantic", "-Werror",
             *(str(ROOT / name) for name in SOURCES), "-o", str(cls.binary)],
            check=True,
        )

    @classmethod
    def tearDownClass(cls):
        cls.build.cleanup()

    def run_case(self, mechanics, customers):
        with tempfile.TemporaryDirectory() as temp:
            folder = pathlib.Path(temp)
            (folder / "Mechanics.txt").write_text(mechanics)
            (folder / "Customers.txt").write_text(customers)
            return subprocess.run([str(self.binary)], cwd=folder,
                                  text=True, capture_output=True)

    def test_committed_sample(self):
        result = self.run_case((ROOT / "Mechanics.txt").read_text(),
                               (ROOT / "Customers.txt").read_text())
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertEqual(len(result.stdout.splitlines()), 15)
        self.assertIn("ds | 01:23 | mechanic 2343", result.stdout)
        self.assertIn("mdaS | 19:33 | UNASSIGNED", result.stdout)

    def test_time_order_and_stable_ties(self):
        result = self.run_case("A 30 10\nB 32 20\n", "later 20 10 0\nfirst 21 9 0\nsecond 21 9 0\n")
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertEqual(result.stdout.splitlines(), [
            "first | 09:00 | mechanic 10",
            "second | 09:00 | mechanic 20",
            "later | 10:00 | mechanic 10",
        ])

    def test_overlaps_and_capacity(self):
        times = "".join(f"c{i} 25 {hour} 0\n" for i, hour in enumerate([0, 1, 2, 3, 4]))
        result = self.run_case("A 30 10\n", times)
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertEqual(result.stdout.count("mechanic 10"), 4)
        self.assertIn("c4 | 04:00 | UNASSIGNED", result.stdout)
        result = self.run_case("A 30 10\n", "a 25 8 15\nb 25 9 0\nc 25 9 15\n")
        self.assertEqual(result.stdout.splitlines(), [
            "a | 08:15 | mechanic 10", "b | 09:00 | UNASSIGNED", "c | 09:15 | mechanic 10",
        ])

    def test_empty_customers(self):
        result = self.run_case("A 30 10\n", "")
        self.assertEqual(result.returncode, 0)
        self.assertEqual(result.stdout, "")

    def test_invalid_customer_time_or_format(self):
        for customer_text in ["x 20 23 30\n", "x 20 9 60\n", "x 20 8\n", "x 20 8 0 extra\n", "x 0 8 0\n"]:
            with self.subTest(customer_text=customer_text):
                result = self.run_case("A 30 10\n", customer_text)
                self.assertEqual(result.returncode, 1)
                self.assertIn("Invalid customer record", result.stderr)
                self.assertEqual(result.stdout, "")

    def test_invalid_mechanic_records(self):
        for mechanics in ["", "A 30 10\nB 35 10\n", "A -2 10\n", "A 30 x\n", "A 30 10 extra\n"]:
            with self.subTest(mechanics=mechanics):
                result = self.run_case(mechanics, "c 20 8 0\n")
                self.assertEqual(result.returncode, 1)
                self.assertEqual(result.stdout, "")

    def test_missing_files_and_bad_cli(self):
        with tempfile.TemporaryDirectory() as temp:
            result = subprocess.run([str(self.binary)], cwd=temp, text=True, capture_output=True)
        self.assertEqual(result.returncode, 1)
        self.assertIn("Cannot open Mechanics.txt", result.stderr)
        result = subprocess.run([str(self.binary), "one"], text=True, capture_output=True)
        self.assertEqual(result.returncode, 2)
        self.assertIn("Usage", result.stderr)

    def test_custom_paths(self):
        with tempfile.TemporaryDirectory() as temp:
            folder = pathlib.Path(temp)
            m = folder / "workers.data"
            c = folder / "clients.data"
            m.write_text("A 30 7\n")
            c.write_text("C 28 23 0\n")
            result = subprocess.run([str(self.binary), str(m), str(c)],
                                    text=True, capture_output=True)
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertEqual(result.stdout.strip(), "C | 23:00 | mechanic 7")


if __name__ == "__main__":
    unittest.main()
