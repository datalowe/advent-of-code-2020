import code_day4_functions as cd4f

# read in raw input
with open("input_day4.txt") as f:
    input_raw = f.read()

# split raw input into a list of passport strings
pass_ls = input_raw.split('\n\n')

# form a generator which converts each passport string into a dictionary of
# passport key-value pairs
pdict_gen = (cd4f.pass_str_to_dict(pass_str) for pass_str in pass_ls)

# form a generator which checks each dictionary of passport key-value pairs
# to see if the passport is valid
pvalid_gen = (cd4f.pass_dict_valid(pass_dict) for pass_dict in pdict_gen)

valid_counter = 0
for pvalid in pvalid_gen:
    valid_counter += pvalid

with open("output_day4_b.txt", "w") as f:
    f.write(str(valid_counter))
