from collections import OrderedDict

from functools import reduce


# define constants
INPUT_FILE_NAME = 'input_day9_example.txt'
PREAMBLE_LEN = 5


def combine_sets(first_set, second_set):
    return first_set.union(second_set)


def solve():
    num_dict = OrderedDict()
    input_nums = (int(i_line.rstrip()) for i_line in open(INPUT_FILE_NAME))
    for inp_n in input_nums:
        print(inp_n)
        if len(num_dict) == PREAMBLE_LEN:
            pre_nums = reduce(combine_sets, num_dict.values())
            if inp_n not in pre_nums:
                incorrect_num = inp_n
                break
            num_dict.popitem(last=False)
        for key in num_dict.keys():
            num_dict[key].add(key + inp_n)
        num_dict[inp_n] = set()
    with open('output_day9_a.txt', 'w') as f:
        f.write(f'{incorrect_num}')


if __name__ == '__main__':
    solve()
