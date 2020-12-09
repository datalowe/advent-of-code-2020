class Accumulator:
    def __init__(self, cmd_tuple):
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
        self.cmd_tuple = cmd_tuple

    def acc(self, arg_val):
        self.acc_val += int(arg_val)
        self.head_position += 1

    def jmp(self, arg_val):
        self.head_position += int(arg_val)

    def nop(self, arg_val):
        self.head_position += 1

    def process_command(self, command_ls):
        cmd, arg_val = command_ls
        self.cmd_dict[cmd](arg_val)

    def process_command_tuple(self):
        while (self.head_position not in self.visited_i_set):
            self.visited_i_set.add(self.head_position)
            self.process_command(self.cmd_tuple[self.head_position])
