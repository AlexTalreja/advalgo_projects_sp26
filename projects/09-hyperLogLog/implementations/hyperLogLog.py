import math
import sys
import mmh3

class HyperLogLog:
    def __init__(self, p):
        self.p = p
        self.num_registers = 1 << p
        self.reg = [0] * self.num_registers

    def add_element(self, value):
        hash = mmh3.hash64(str(value), seed=0xADC83B19, signed=False)[0]
        register_index = hash >> (64 - self.p)
        remaining_bits = 64 - self.p
        w = hash & ((1 << remaining_bits) - 1)
        if w == 0:
            num_leading_zeros = remaining_bits + 1
        else:
            num_leading_zeros = (remaining_bits - w.bit_length()) + 1
        if num_leading_zeros > self.reg[register_index]:
            self.reg[register_index] = num_leading_zeros

    def estimate_cardinality(self):
        num_registers = self.num_registers
        if num_registers == 16: # bias correction from hyper log log paper
            bias_correction = 0.673
        elif num_registers == 32:
            bias_correction = 0.697
        elif num_registers == 64:
            bias_correction = 0.709
        else:
            bias_correction = 0.7213 / (1 + 1.079 / num_registers)

        harmonic_sum = sum(2.0 ** (-r) for r in self.reg)
        cardinality_estimate = bias_correction * num_registers * num_registers / harmonic_sum

        num_registers_empty = self.reg.count(0)
        if cardinality_estimate <= 2.5 * num_registers and num_registers_empty > 0:
            return num_registers * math.log(num_registers / num_registers_empty)

        two64 = float(1 << 64)
        if cardinality_estimate > two64 / 30.0:
            return -two64 * math.log(1.0 - cardinality_estimate / two64)

        return cardinality_estimate

if __name__ == "__main__":
    if len(sys.argv) > 1:
        t = open(sys.argv[1], "r", encoding="utf-8").read().split()
    else:
        t = sys.stdin.read().split()

    precision = 14
    if len(sys.argv) > 2:
        precision = int(sys.argv[2])

    h = HyperLogLog(precision)
    for tok in t:
        h.add_element(tok)

    sys.stdout.write(str(int(round(h.estimate_cardinality()))))
