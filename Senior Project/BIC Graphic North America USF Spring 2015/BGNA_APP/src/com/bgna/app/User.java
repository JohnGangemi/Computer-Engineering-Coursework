package com.bgna.app;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Random;

public class User {

	private int id;
	private String username;
	private String password;
	private String first_name;
	private String last_name;
	private String birth_month;
	private String birth_day;
	private int reg_code;
	private int registered;
	private String role;
	private String security_q1;
	private String security_q2;
	private String security_q3;
	private String security_ans1;
	private String security_ans2;
	private String security_ans3;
	
	public User() {
		this.id = 0;
		this.username = null;
		this.password = null;
		this.first_name = null;
		this.last_name = null;
		this.birth_month = null;
		this.birth_day = null;
		this.reg_code = 0;
		this.registered = 0;
		this.role = null;
		this.security_q1 = null;
		this.security_q2 = null;
		this.security_q3 = null;
		this.security_ans1 = null;
		this.security_ans2 = null;
		this.security_ans3 = null;
	}
	
	public void setAll(ResultSet rs) {
		try {
			this.id = rs.getInt("id");
			this.username = rs.getString("username");
			this.password = rs.getString("password");
			this.first_name = rs.getString("first_name");
			this.last_name = rs.getString("last_name");
			this.birth_month = rs.getString("birth_month");
			this.birth_day = rs.getString("birth_day");
			this.reg_code = rs.getInt("reg_code");
			this.registered = rs.getInt("registered");
			this.role = rs.getString("role");
			this.security_q1 = rs.getString("question1");
			this.security_q2 = rs.getString("question2");
			this.security_q3 = rs.getString("question3");
			this.security_ans1 = rs.getString("answer1");
			this.security_ans2 = rs.getString("answer2");
			this.security_ans3 = rs.getString("answer3");
		} catch (SQLException e) {
			e.printStackTrace();
		}
	}
	
	public String getRandomQuestion() {
		Random rand = new Random();
		int ques = rand.nextInt(3) + 1;
		
		switch(ques)
		{
			case 1:
				return getSecurity_q1();
			case 2:
				return getSecurity_q2();
			case 3:
				return getSecurity_q3();
			default:
				return getSecurity_q1();				
		}
	}
	
	public String getUsername() {
		return username;
	}

	public void setUsername(String username) {
		this.username = username;
	}

	public String getPassword() {
		return password;
	}

	public void setPassword(String password) {
		this.password = password;
	}

	public String getFirst_name() {
		return first_name;
	}

	public void setFirst_name(String first_name) {
		this.first_name = first_name;
	}

	public String getLast_name() {
		return last_name;
	}

	public void setLast_name(String last_name) {
		this.last_name = last_name;
	}

	public String getBirth_month() {
		return birth_month;
	}

	public void setBirth_month(String birth_month) {
		this.birth_month = birth_month;
	}

	public String getBirth_day() {
		return birth_day;
	}

	public void setBirth_day(String birth_day) {
		this.birth_day = birth_day;
	}

	public int getReg_code() {
		return reg_code;
	}

	public void setReg_code(int reg_code) {
		this.reg_code = reg_code;
	}

	public int getRegistered() {
		return registered;
	}

	public void setRegistered(int registered) {
		this.registered = registered;
	}

	public String getRole() {
		return role;
	}

	public void setRole(String role) {
		this.role = role;
	}

	public String getSecurity_q1() {
		return security_q1;
	}

	public void setSecurity_q1(String security_q1) {
		this.security_q1 = security_q1;
	}

	public String getSecurity_q2() {
		return security_q2;
	}

	public void setSecurity_q2(String security_q2) {
		this.security_q2 = security_q2;
	}

	public String getSecurity_q3() {
		return security_q3;
	}

	public void setSecurity_q3(String security_q3) {
		this.security_q3 = security_q3;
	}

	public String getSecurity_ans1() {
		return security_ans1;
	}

	public void setSecurity_ans1(String security_ans1) {
		this.security_ans1 = security_ans1;
	}

	public String getSecurity_ans2() {
		return security_ans2;
	}

	public void setSecurity_ans2(String security_ans2) {
		this.security_ans2 = security_ans2;
	}

	public String getSecurity_ans3() {
		return security_ans3;
	}

	public void setSecurity_ans3(String security_ans3) {
		this.security_ans3 = security_ans3;
	}

	public int getId() {
		return id;
	}

}
