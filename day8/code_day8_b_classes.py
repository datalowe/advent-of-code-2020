class Accumulator:
    def __init__(self, cmd_list):
        # accumulator value
        self.acc_val = 0
        # index from which command reader head will currently
        # try to read
        self.head_position = 0
        # set of indices that reader head has visited
        self.visited_i_set = set()
        self.cmd_dict = {
            'acc': self.acc,
            'jmp': self.jmp,
            'nop': self.nop,
        }
        self.cmd_list = cmd_list
        self.orig_cmd_list = cmd_list
        # set of indices of nop/jmp commands visited before infinite
        # loop begins
        self.preloop_nj_is = set()

    def acc(self, arg_val):
        self.acc_val += int(arg_val)
        self.head_position += 1

    def jmp(self, arg_val):
        self.head_position += int(arg_val)

    def nop(self, arg_val):
        self.head_position += 1

    def process_command(self, command_ls, find_njs = False):
        cmd, arg_val = command_ls
        if cmd != 'acc':
            self.preloop_nj_is.add(self.head_position)
        self.cmd_dict[cmd](arg_val)

    def process_command_list(self, find_njs = False):
        cmd_len = len(self.cmd_list)
        while (self.head_position not in self.visited_i_set):
            if self.head_position >= cmd_len:
                return 'Finished to end'
            self.visited_i_set.add(self.head_position)
            self.process_command(
                self.cmd_list[self.head_position],
                find_njs = find_njs
            )
        return 'Hit loop'

    def flip_nop_jmp(self, cmd_index):
        if self.cmd_list[cmd_index][0] == 'nop':
            self.cmd_list[cmd_index][0] = 'jmp'
        elif self.cmd_list[cmd_index][0] == 'jmp':
            self.cmd_list[cmd_index][0] = 'nop'

    def debug_and_run(self):
        self.process_command_list(find_njs = True)
        self.reset()
        found_faulty = False
        while not found_faulty:
            candidate_index = self.preloop_nj_is.pop()
            self.flip_nop_jmp(candidate_index)
            if self.process_command_list() == 'Finished to end':
                found_faulty = True
            else:
                self.reset()

    def reset(self):
        self.cmd_list = [[x[0], x[1]] for x in self.orig_cmd_list]
        self.head_position = 0
        self.acc_val = 0
        self.visited_i_set = set()
