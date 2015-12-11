package com.bgna.app;

import java.sql.*;
import com.vaadin.ui.Alignment;
import com.vaadin.ui.Button;
import com.vaadin.ui.FormLayout;
import com.vaadin.ui.Label;
import com.vaadin.ui.Panel;
import com.vaadin.ui.PasswordField;
import com.vaadin.ui.TextField;
import com.vaadin.ui.UI;
import com.vaadin.ui.VerticalLayout;
import com.vaadin.ui.Button.ClickEvent;

@SuppressWarnings("serial")
public class LoginView extends VerticalLayout {
	
	DatabaseHelper db;
	User emp;
	
	private Label info;
	private TextField usrname_txt;
	private PasswordField passwrd_txt;
	private Button login_btn;
	private Button new_btn;
	private Button lost_btn;
	
	public LoginView()
	{
		this.db = new DatabaseHelper();
		this.emp = new User(); // clear current user (logout, browser refresh)
		
		// debug code
		System.out.println("Login user: " + emp.getUsername());
		
		buildView();
	}
		
	private void buildView()
	{	
		// login frame
		Panel pane = new Panel("Welcome");
		pane.setSizeUndefined();
		
		// login input field layout
		usrname_txt = new TextField("Username");
		usrname_txt.setWidth("15em");
		usrname_txt.focus();

		passwrd_txt = new PasswordField("Password");
		passwrd_txt.setWidth("15em");

		FormLayout form = new FormLayout();
		form.setSizeUndefined();
		form.addComponent(usrname_txt);
		form.addComponent(passwrd_txt);
		
		// login content layout		
		login_btn = new Button("Login");
		login_btn.setDescription("Click here to login!");
		login_btn.setSizeFull();
		login_btn.setStyleName("primary");
		
		new_btn = new Button("New User?");
		new_btn.setDescription("Click here to register!");
		new_btn.setSizeFull();
		
		lost_btn = new Button("Lost Password?");
		lost_btn.setDescription("Click here to create a new password!");
		lost_btn.setSizeFull();

		info = new Label();
		info.setSizeUndefined();
		info.setValue("Please enter username and password");
		
		Label gap = new Label();
		gap.setHeight("1em");
		
		VerticalLayout content = new VerticalLayout();
		content.setSizeUndefined();
		content.setSpacing(true);
		content.setMargin(true);
		content.addComponent(info);
		content.setComponentAlignment(info, Alignment.MIDDLE_CENTER);
		content.addComponent(form);
		content.setComponentAlignment(form, Alignment.MIDDLE_CENTER);
		content.addComponent(login_btn);
		content.addComponent(gap);
		content.addComponent(new_btn);
		content.addComponent(lost_btn);
		
		// add 'login content layout' to 'login frame'
		pane.setContent(content);
		
		// root layout
		this.setMargin(true);
		this.addComponent(pane);
		this.setComponentAlignment(pane, Alignment.TOP_CENTER);

		
		//
		// user interaction
		//				
		login_btn.addClickListener(event -> handleLogin(event)); 	
		new_btn.addClickListener(event -> handleNewUser(event));
		lost_btn.addClickListener(event -> handleLostPassword(event));	
	}

	private void handleLogin(ClickEvent event)
	{		
		final String un = usrname_txt.getValue().trim();
		final String pw = passwrd_txt.getValue().trim();
		
		if(un.isEmpty() && pw.isEmpty())
		{					
			info.setValue("One or more fields are empty");
		}
		else if(un.isEmpty())
		{
			info.setValue("Remember to enter a username");
		}
		else if(pw.isEmpty())
		{
			info.setValue("Remember to enter a password");
		}
		else
		{	
			boolean valid = false;
			final String bg_un = "bg" + un;
			
			try {		
				// Database call execution		
				ResultSet rs = db.getStatement().executeQuery("select * from employee");
				
				// validate against database
				while(rs.next())
				{
					if(bg_un.equalsIgnoreCase(rs.getString("username")) && pw.equalsIgnoreCase(rs.getString("password")))
					{
						emp.setAll(rs);
						
						// debug code
						System.out.println("Login user set as: " + emp.getUsername());
						
						valid = true;
						break;
					}
				}
	
				// release JDBC resources consumed by ResultSet 'rs'
				rs.close();
				
				if(valid)
				{
					if(emp.getRole().equalsIgnoreCase("super"))
						UI.getCurrent().setContent(new SupervisorView(emp));
					else if(emp.getRole().equalsIgnoreCase("user"))
						UI.getCurrent().setContent(new AccountServiceView(emp));
				}
				else
				{
					info.setValue("Incorrect username and/or password");
					usrname_txt.focus();
				}
			
			} catch (SQLException e) {
				e.printStackTrace();
			}
		}
	}
	
	private void handleNewUser(ClickEvent event)
	{
		UI.getCurrent().setContent(new AccountReg1View());
	}
	
	private void handleLostPassword(ClickEvent event)
	{
		UI.getCurrent().setContent(new PasswordRec1View());
	}

}
