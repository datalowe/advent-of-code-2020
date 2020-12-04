import re

# define set which holds all keys which are required for a passport
# to be valid
REQ_SET = {
    "byr", "iyr", "eyr", "hgt",
    "hcl", "ecl", "pid"
}

# read in raw input
with open("input_day4.txt") as f:
    input_raw = f.read()

# split raw input into a list of passport strings
pass_ls = input_raw.split('\n\n')

# form a generator which converts each passport string into a set of
# included passport keys
pass_sets = (set(re.findall("([a-z]{3}):", pass_str)) for pass_str in pass_ls)

# check how many of generated passport key sets include all the necessary
# keys (ie are supersets of the set of all required keys)
num_valid = sum([pass_set.issuperset(REQ_SET) for pass_set in pass_sets])

with open("output_day4_a.txt", "w") as f:
    f.write(str(num_valid))
