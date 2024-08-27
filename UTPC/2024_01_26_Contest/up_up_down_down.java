import java.util.*;
import java.io.*;

public class Solution {
	
	static String codeStr = "up, up, down, down, left, right, left, right, b, a, start";

	public static void main(String[] args) throws IOException {
		Scanner in = new Scanner(System.in);
		String[] line = in.nextLine().split(" ");
		String[] code = codeStr.split(", ");
		int score = 0;
		for(int i = 0; i < code.length; i++) {
			if(code[i].equals(line[i]))
				score++;
		}
		System.out.println(score);
	}
}