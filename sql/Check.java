
import java.util.Scanner;

public class Check {
	static {
	      System.loadLibrary("fileData"); 
	}
	      private native boolean addRow(String row,String s1,String s2, String s3, String s4);
	      private native boolean removeRow(String s1);
	      private native boolean updateRow(String r, int c, String n);
	      private native int searchRow(int c, String data);
	      public static void main(String[] args) {
	  		
	  		Scanner sc=new Scanner(System.in);
	  		Check obj =new Check();
			int i =1;
	  		while(true) {
	  			
	  			System.out.println("1.add \n 2.remove \n 3.update \n 4.search");
				int c=sc.nextInt();
				sc.nextLine();
	  			switch(c) {
	  			case 1: {
					System.out.println("name");
	  				String name=sc.nextLine();
					System.out.println("age");
	  				String age=sc.nextLine();
					System.out.println("date");
	  				String date=sc.nextLine();
					System.out.println("city");
	  				String city=sc.nextLine();
					
	  				obj.addRow(String.valueOf(i),name,age,date,city);
					i++;
	  			};break;
	  			
	  			case 2: {
					System.out.println("deleteRow");
	  				String row=sc.nextLine();
	  				obj.removeRow(row);
	  			};break;
	  			
	  			case 3: {
					System.out.println("Row");
	  				String row=sc.nextLine();
					System.out.println("1)name 2)age 3)dob 4)city");
	  				int col= sc.nextInt();
					sc.nextLine();
					System.out.println("data");
					String data=sc.nextLine();
	  				obj.updateRow(row,col,data);
	  			};break;
	  			
	  			case 4: {
					System.out.println("1)name 2)age 3)dob 4)city");
	  				int col=sc.nextInt();
					sc.nextLine();
					System.out.println("data");
					String data=sc.nextLine();
	  				int row=obj.searchRow(col,data);
						System.out.println("data is present at"+row);
	  			};break;
	  			}
	  			}
	  		
	  		
	  	
	   }
}
