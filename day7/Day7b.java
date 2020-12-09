import java.util.HashMap;
import java.util.HashSet;
import java.util.stream.Stream;

import java.util.regex.Pattern;
import java.util.regex.Matcher;

import java.nio.file.Paths;
import java.nio.file.Path;
import java.nio.file.Files;
import java.nio.file.StandardOpenOption;

import java.io.IOException;

public class Day7b {
    // a hashmap where keys are 'parent' colors, and
    // values are keys' 'child' numbers/colors, ie colors and numbers
    // of bags which must be contained by bags of the 'parent' color
    static HashMap<String, HashSet<String[]>> parentColors = new
            HashMap<String, HashSet<String[]>>();

    public static void main(String[] args) {
        // form path instance pointing to input
        Path inPath = Paths.get("/Users/lowe/Documents/Programmering/misc_code/advent_of_code/aoc_2020/day7/input_day7.txt");

        try {
            // form a stream streaming input data lines
            Stream<String> inStream = Files.lines(inPath);
            // parse every input line and add info to parentColors
            // HashMap instance
            inStream.forEach(line -> parseBagStr(line));
            inStream.close();
        } catch (IOException e) {
            System.out.println("Couldn't find the input file.");
            e.printStackTrace();
        }

        String startColor = "shiny gold";

        // go through all multi-generational children of the shiny gold
        // bag/color node and tally up their counts
        int innerBagTally = traverseColors(startColor);

        Path outPath = Paths.get("output_day7_b.txt");

        try {
            Files.write(
                outPath,
                String.format("%d", innerBagTally).getBytes("utf-8"),
                StandardOpenOption.CREATE
            );
        } catch (IOException e) {
            System.out.println("Unable to write to output file.");
            e.printStackTrace();
        }

    }

    /**
     * Parse a 'bag' string, extracting the data about child/parent
     * color relationships and inserting them into the parentColors
     * attribute/HashMap instance.
     * @param bagStr
     */
    public static void parseBagStr(CharSequence bagStr) {
        // regex patterns for matching 'parent'/'child' colors
        Pattern parentPatt = Pattern.compile("([a-z ]+)(?= bags con)");
        Pattern childPatt = Pattern.compile("([0-9]+) ([a-z ]+)(?= bag)");

        Matcher parentMatcher = parentPatt.matcher(bagStr);
        Matcher childMatcher = childPatt.matcher(bagStr);

        String childNumber;
        String childColor;
        String[] childInfo;
        HashSet<String[]> childSet;

        parentMatcher.find();
        String parentColor = parentMatcher.group();

        if (!parentColors.containsKey(parentColor)) {
            parentColors.put(parentColor, new HashSet<String[]>());
        }
        childSet = parentColors.get(parentColor);

        while (childMatcher.find()) {
            // extract the part eg '2' in '2 yellow bags'
            childNumber = childMatcher.group(1);
            // extract the part eg 'yellow' in '2 yellow bags'
            childColor = childMatcher.group(2);
            childInfo = new String[]{childNumber, childColor};
            childSet.add(childInfo);
        }
    }

    /**
     * Recursive function that traverses the hashmap of child/
     * parent colors, continuing to child nodes and adding their
     * numbers.
     * @param startColor Color/parentColors key to start traversing
     * from.
     */
    public static int traverseColors(String startColor) {
        int totalCount = 0;
        int childCount;
        if (parentColors.containsKey(startColor)) {
            for (String[] childBag: parentColors.get(startColor)) {
                childCount = Integer.parseInt(childBag[0]);
                totalCount += childCount + childCount * traverseColors(childBag[1]);
                // innerBagTally += ;
                // ;
            }
        }
        return totalCount;
    }
}
