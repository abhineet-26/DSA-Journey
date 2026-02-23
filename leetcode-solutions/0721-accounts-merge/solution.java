import java.util.*;

class Solution {
    public List<List<String>> accountsMerge(List<List<String>> accounts) {
        Map<String, Integer> emailToId = new HashMap<>();
        Map<String, String> emailToName = new HashMap<>();
        int id = 0;

        for (List<String> acc : accounts) {
            String name = acc.get(0);
            for (int i = 1; i < acc.size(); i++) {
                String email = acc.get(i);
                if (!emailToId.containsKey(email)) {
                    emailToId.put(email, id++);
                    emailToName.put(email, name);
                }
            }
        }

        int[] parent = new int[id];
        int[] rank = new int[id];
        for (int i = 0; i < id; i++) parent[i] = i;

        for (List<String> acc : accounts) {
            String firstEmail = acc.get(1);
            int firstId = emailToId.get(firstEmail);
            for (int i = 2; i < acc.size(); i++) {
                String email = acc.get(i);
                int eid = emailToId.get(email);
                union(firstId, eid, parent, rank);
            }
        }

        Map<Integer, List<String>> groups = new HashMap<>();
        for (String email : emailToId.keySet()) {
            int root = find(emailToId.get(email), parent);
            groups.computeIfAbsent(root, k -> new ArrayList<>()).add(email);
        }

        List<List<String>> res = new ArrayList<>();
        for (List<String> emails : groups.values()) {
            Collections.sort(emails);
            String name = emailToName.get(emails.get(0));
            List<String> acc = new ArrayList<>();
            acc.add(name);
            acc.addAll(emails);
            res.add(acc);
        }
        return res;
    }

    private int find(int x, int[] parent) {
        if (parent[x] != x) parent[x] = find(parent[x], parent);
        return parent[x];
    }

    private void union(int x, int y, int[] parent, int[] rank) {
        int rx = find(x, parent), ry = find(y, parent);
        if (rx == ry) return;
        if (rank[rx] < rank[ry]) parent[rx] = ry;
        else if (rank[rx] > rank[ry]) parent[ry] = rx;
        else {
            parent[ry] = rx;
            rank[rx]++;
        }
    }
}

