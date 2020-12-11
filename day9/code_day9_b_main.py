from collections import OrderedDict

from functools import reduce


# define constants
INPUT_FILE_NAME = 'input_day9.txt'
PREAMBLE_LEN = 25

class Snowball:
    def __init__(self, start_val, activated=False):
        self.activated = activated
        self.min_val = start_val
        self.max_val = start_val

    def activate(self):
        self.activated = True

    def is_active(self):
        return self.activated

    def __repr__(self):
        return f'Snowball. min_val: {self.min_val}. max_val: {self.max_val}'


def combine_sets(first_set, second_set):
    return first_set.union(second_set)


def solve():
    num_dict = OrderedDict()
    input_nums = (int(i_line.rstrip()) for i_line in open(INPUT_FILE_NAME))
    for inp_n in input_nums:
        if len(num_dict) == PREAMBLE_LEN:
            pre_nums = reduce(combine_sets, num_dict.values())
            if inp_n not in pre_nums:
                incorrect_num = inp_n
                break
            num_dict.popitem(last=False)
        for key in num_dict.keys():
            num_dict[key].add(key + inp_n)
        num_dict[inp_n] = set()

    snowball_dict = dict()
    input_nums = (int(i_line.rstrip()) for i_line in open(INPUT_FILE_NAME))
    throwaway_snowball = Snowball(0)
    inactive_snowball = throwaway_snowball
    for inp_n in input_nums:
        old_dict = snowball_dict
        snowball_dict = dict()
        for key in old_dict:
            snowball = old_dict[key]
            if snowball.min_val > inp_n:
                snowball.min_val = inp_n
            if snowball.max_val < inp_n:
                snowball.max_val = inp_n
            snowball_dict[key+inp_n] = snowball
        if incorrect_num in snowball_dict and snowball_dict[incorrect_num].is_active():
            match_snowball = snowball_dict[incorrect_num]
            break
        inactive_snowball.activate()
        inactive_snowball = Snowball(inp_n)
        snowball_dict[inp_n] = inactive_snowball

    with open('output_day9_a.txt', 'w') as f:
        f.write(f'{incorrect_num}')

    with open('output_day9_b.txt', 'w') as f:
        f.write(f'{match_snowball.min_val + match_snowball.max_val}')


if __name__ == '__main__':
    solve()
