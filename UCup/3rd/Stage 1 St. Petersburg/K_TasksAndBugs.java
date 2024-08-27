import java.util.*;
import java.io.*;

public class Solution {
	
	public static int getNum (String s) {
		return Integer.parseInt(s.split("-")[1]);
	}
	
	public static String toNum(int id) {
		return "CS-" + id;
	}

	public static void main(String[] args) throws IOException {
		Scanner in = new Scanner(System.in);
		TreeMap<Integer, ArrayList<Integer>> seen = new TreeMap<>();
		while(in.hasNextLine()) {
			String[] line = in.nextLine().split(": ");
			int bug = getNum(line[0]);
			String[] tasks = line[1].split(", ");
			for(String s : tasks) {
				int task = getNum(s);
				if(!seen.containsKey(task))
					seen.put(task, new ArrayList<>());
				seen.get(task).add(bug);
			}
		}
		for(int task : seen.keySet()) {
			System.out.print(toNum(task) + ": ");
			Collections.sort(seen.get(task));
			for(int i = 0; i < seen.get(task).size(); i++) {
				int bug = seen.get(task).get(i);
				if(i > 0)
					System.out.print(", ");
				System.out.print(toNum(bug));
			}
			System.out.println();
		}
	}
}