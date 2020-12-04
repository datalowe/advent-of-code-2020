import re


def pass_dict_valid(pass_dict):
    """
    Goes through all key:value pairs of a passport dictionary and returns
    True if they are all valid, otherwise False.
    :param pass_dict: The passport dictionary to validate.
    :type pass_dict: dict
    :return: True if passport is valid, otherwise False.
    :rtype: bool
    """
    check_dict = {
        'byr': year_check_factory(1920, 2002),
        'iyr': year_check_factory(2010, 2020),
        'eyr': year_check_factory(2020, 2030),
        'hgt': height_valid,
        'hcl': hair_color_valid,
        'ecl': eye_color_valid,
        'pid': passport_id_valid
    }
    if not set(pass_dict.keys()).issuperset(set(check_dict.keys())):
        return False
    for key in check_dict:
        if not check_dict[key](pass_dict[key]):
            return False
    return True


def year_check_factory(start_range, end_range):
    """
    Produces a function which takes in a string and checks if it holds
    a value that is in range [start_range, end_range].
    :param start_range: Lower end (inclusive) of range.
    :type start_range: int
    :param end_range: Upper end (inclusive) of range.
    :type end_range: int
    :return: A function which returns True if a string passed to it
    holds an integer within [start_range, end_range], otherwise False.
    :rtype: function
    """
    def year_check(year_str):
        if start_range <= int(year_str) <= end_range:
            return True
        return False
    return year_check

def height_valid(height):
    """
    Takes in a string which holds a height and checks if it is valid.
    :param height: A height.
    :type height: str
    :return: True if height is valid. If the string ends with 'cm', the height
    is valid if the integer value is in range [150, 193]. If the string ends
    with 'in', the integer value is valid if in range [59, 76]. Otherwise
    returns False.
    :rtype: bool
    """
    metric_type = height[-2:]
    if metric_type == "cm":
        start_range, end_range = (150, 193)
    elif metric_type == "in":
        start_range, end_range = (59, 76)
    else:
        return False
    if start_range <= int(height[:-2]) <= end_range:
        return True
    return False

def hair_color_valid(hair_color):
    """
    Takes in a string which holds a hair color and checks if it is valid.
    :param hair_color: A hair color.
    :type hair_color: str
    :return: True if the passed string consists of a '#' followed by exactly
    six characters 0-9 or a-f. Otherwise returns False.
    :rtype: bool
    """
    return bool(re.match("^#[\da-f]{6}$", hair_color))

def eye_color_valid(eye_color):
    """
    Takes in a string which holds an eye color and checks if it is valid.
    :param eye_color: An eye color.
    :type eye_color: str
    :return: True if the passed string is one of:
    'amb', 'blu', 'brn', 'gry', 'grn', 'hzl', 'oth.' Otherwise returns False.
    :rtype: bool
    """
    valid_colors = {
        'amb', 'blu', 'brn', 'gry',
        'grn', 'hzl', 'oth'
    }
    return eye_color in valid_colors

def passport_id_valid(pass_id):
    """
    Takes in a string which holds a passport ID and checks if it is valid.
    :param pass_id: A passport ID.
    :type pass_id: str
    :return: True if the passed string consists of a nine-digit number,
    including leading zeroes. Otherwise returns False.
    :rtype: bool
    """
    return bool(re.match("^\d{9}$", pass_id))

def country_id_valid(country_id):
    """
    Takes in a string which holds a country ID and checks if it is valid.
    :param pass_id: A country ID.
    :type pass_id: str
    :return: True if the passed string consists of a nine-digit number,
    including leading zeroes. Otherwise returns False.
    :rtype: bool
    """


def pass_str_to_dict(pass_str):
    """
    Converts a passport string to a dictionary of passport key:value pairs.
    :param pass_str: Passport string.
    :type pass_str: str
    :return: A dictionary of passport key:value pairs.
    :rtype: dict
    """
    pass_dict = {}
    key_val_tups = re.findall("([a-z]+):([#0-9a-zA-Z]+)", pass_str)
    for key_val_tup in key_val_tups:
        pass_dict[key_val_tup[0]] = key_val_tup[1]
    return pass_dict
