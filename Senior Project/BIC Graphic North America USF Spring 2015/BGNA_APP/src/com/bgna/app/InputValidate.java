package com.bgna.app;

public class InputValidate {
	
	public InputValidate() {
	}
	
	public boolean isBirthDateValid(String month, String day)
	{
		int num = Integer.parseInt(day);
		
		if(month == "April"
				|| month == "June"
				|| month == "September"
				|| month == "November")
		{
			if(num > 30)
				return false;
		}
		else if(month == "February")
		{
			if(num > 29)
				return false;
		}
		
		return true;
	}
	
	public boolean isPasswordPolicy(String password, String username, String first, String last)
	{	
		if(password.length() < 6 
				|| password.contains(" ") 
				|| password.toLowerCase().contains(username.toLowerCase())
				|| password.toLowerCase().contains(first.toLowerCase())
				|| password.toLowerCase().contains(last.toLowerCase()))
			return false;
		
		char[] x = password.toCharArray();
		int countNum = 0;
		int countCapital = 0;
		int countLower = 0;
		
		for(int i = 0; i < password.length(); i++)
		{
			if(Character.isDigit(x[i]))
				countNum++;
			else if(Character.isUpperCase(x[i]))
				countCapital++;
			else if(Character.isLowerCase(x[i]))
				countLower++;
			else
				return false;
		}
		
		if(countNum < 1 || countCapital < 1 || countLower < 1)
			return false;
		
		return true;
	}

	public boolean isSpecialChars(String str)
	{
		char[] x = str.toCharArray();
		
		for(int i = 0; i < str.length(); i++)
		{
			if(!(Character.isLetter(x[i]) || Character.isDigit(x[i]) || Character.isSpaceChar(x[i])))
				return true;
		}
			
		return false;
	}
	
	public boolean noneEmpty(String[] items)
	{
		for(int i = 0; i < items.length; i++)
			if(items[i].isEmpty())
				return false;
		
		return true;
	}
	
}
