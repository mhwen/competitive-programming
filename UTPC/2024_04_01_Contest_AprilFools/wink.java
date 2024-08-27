import java.util.*;
import java.io.*;

public class wink {

	public static void main(String[] args) throws IOException {
		String s = "To celebrate April Fools' Day this year, we will absolutely not be hosting a surprise contest on April 1st! But, just for laughs, what if there was to be an unexpected contest at 5:30pm in GDC 2.216 on April 1st, 2024? Just a heads up, this contest won't be your typical run-of-the-mill affair. And hey, there most certainly won't be any free food 🌮 at this (nonexistent) contest!!! Hope to see you all there, or not!";
		String[] arr = s.split(" ");
		Scanner in = new Scanner(System.in);
		String s1 = in.next();
		for(int i = 0; i < arr.length; i++) {
			if(arr[i].equals(s1)) {
				System.out.println(arr[i+1]);
				break;
			}
		}
	}
}