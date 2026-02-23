import java.util.*;

class Solution {
    public String frequencySort(String s) {
        Map<Character, Integer> freq = new HashMap<>();
        for (char c : s.toCharArray()) freq.put(c, freq.getOrDefault(c, 0) + 1);

        List<Character> chars = new ArrayList<>(freq.keySet());
        chars.sort((a, b) -> freq.get(b) - freq.get(a));

        StringBuilder sb = new StringBuilder();
        for (char c : chars) {
            int count = freq.get(c);
            for (int i = 0; i < count; i++) sb.append(c);
        }
        return sb.toString();
    }
}

