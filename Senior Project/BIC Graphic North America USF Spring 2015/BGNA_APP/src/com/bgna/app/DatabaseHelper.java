package com.bgna.app;

import java.sql.*;

public class DatabaseHelper {

	private final String URL = "jdbc:mysql://localhost:3306/bicusf";
	private final String USER = "root";
	private final String PASS = "pass";
	
	DatabaseHelper() {
		try {
			Class.forName("com.mysql.jdbc.Driver");
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		}
	}
	
	public String getURL() {
		return URL;
	}

	public String getUSER() {
		return USER;
	}

	public String getPASS() {
		return PASS;
	}
	
	public Connection getConnection() {
		Connection conn = null;
		
		try {
			conn = DriverManager.getConnection(URL, USER, PASS);
		} catch (SQLException e) {
			e.printStackTrace();
		}
		
		return conn;
	}
	
	public Statement getStatement() {
		Statement state = null;
		
		try {
			state = getConnection().createStatement();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		
		return state;
	}

}
