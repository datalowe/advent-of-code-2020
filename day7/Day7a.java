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

public class Day7a {
    // a hashmap where keys are 'child' colors, and
    // values are keys' 'parent' colors, ie colors which
    // can contain bags of the 'child' color
    static HashMap<String, HashSet<String>> childColors = new
            HashMap<String, HashSet<String>>();

    // a set which will hold all possible outermost bag colors
    static HashSet<String> outermostColors = new HashSet<String>();

    public static void main(String[] args) {
        // form path instance pointing to input
        Path inPath = Paths.get("/Users/lowe/Documents/Programmering/misc_code/advent_of_code/aoc_2020/day7/input_day7.txt");

        try {
            // form a stream streaming input data lines
            Stream<String> inStream = Files.lines(inPath);
            // parse every input line and add info to childColors
            // HashMap instance
            inStream.forEach(line -> parseBagStr(line));
            inStream.close();
        } catch (IOException e) {
            System.out.println("Couldn't find the input file.");
            e.printStackTrace();
        }

        String startColor = "shiny gold";

        traverseColors(startColor);

        int answer = outermostColors.size();

        Path outPath = Paths.get("output_day7_a.txt");

        try {
            Files.write(
                outPath,
                String.format("%d", answer).getBytes("utf-8"),
                StandardOpenOption.CREATE
            );
        } catch (IOException e) {
            System.out.println("Unable to write to output file.");
            e.printStackTrace();
        }

    }

    /**
     * Parse a 'bag' string, extracting the data about child/parent
     * color relationships and inserting them into the childColors
     * attribute/HashMap instance.
     * @param bagStr
     */
    public static void parseBagStr(CharSequence bagStr) {
        // regex patterns for matching 'parent'/'child' colors
        Pattern parentPatt = Pattern.compile("([a-z ]+)(?= bags con)");
        Pattern childPatt = Pattern.compile("(?<=[0-9] )([a-z ]+)(?= bag)");

        Matcher parentMatcher = parentPatt.matcher(bagStr);
        Matcher childMatcher = childPatt.matcher(bagStr);

        String childColor;
        HashSet<String> parentSet;

        parentMatcher.find();
        String parentColor = parentMatcher.group();
        while (childMatcher.find()) {
            childColor = childMatcher.group();
            if (!childColors.containsKey(childColor)) {
                childColors.put(childColor, new HashSet<String>());
            }
            parentSet = childColors.get(childColor);
            if (!parentSet.contains(parentColor)) {
                parentSet.add(parentColor);
            }
        }
    }

    /**
     * Recursive function that traverses the hashmap of child/
     * parent colors, continuing to parent nodes as long as their
     * values haven't already been added to the outermostColors
     * set.
     * @param startColor Color/childColors key to start traversing
     * from.
     */
    public static void traverseColors(String startColor) {
        for (String parentColor: childColors.get(startColor)) {
            if (!outermostColors.contains(parentColor)) {
                outermostColors.add(parentColor);
                if (childColors.containsKey(parentColor)) {
                    traverseColors(parentColor);
                }
            }
        }
    }
}
