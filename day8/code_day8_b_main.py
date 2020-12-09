from code_day8_b_classes import Accumulator

def solve():
    INPUT_FILE_NAME = 'input_day8.txt'
    raw_inputs = (i_line for i_line in open(INPUT_FILE_NAME))
    command_lists = list(r_inp.rstrip().split(' ') for r_inp in raw_inputs)
    accumulator_singleton = Accumulator(command_lists)
    accumulator_singleton.debug_and_run()
    with open('output_day8_b.txt', 'w') as f:
        f.write(str(accumulator_singleton.acc_val))

if __name__ == '__main__':
    solve()
