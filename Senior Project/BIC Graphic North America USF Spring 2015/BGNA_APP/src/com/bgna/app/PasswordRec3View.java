package com.bgna.app;

import java.sql.SQLException;

import com.vaadin.ui.Alignment;
import com.vaadin.ui.Button;
import com.vaadin.ui.FormLayout;
import com.vaadin.ui.Label;
import com.vaadin.ui.Panel;
import com.vaadin.ui.PasswordField;
import com.vaadin.ui.TextArea;
import com.vaadin.ui.UI;
import com.vaadin.ui.VerticalLayout;
import com.vaadin.ui.Button.ClickEvent;

@SuppressWarnings("serial")
public class PasswordRec3View extends VerticalLayout {

	DatabaseHelper db;
	InputValidate iv;
	User emp;
	
	private Button submit;
	private Button cancel;
	private Label info;
	private PasswordField new_txt;
	private PasswordField confirm_txt;
	
	public PasswordRec3View(User emp)
	{
		db = new DatabaseHelper();
		iv = new InputValidate();
		this.emp = emp;
		buildView();
	}
	
	private void buildView()
	{
		// main frame
		Panel pane = new Panel("Change Password");
		pane.setSizeUndefined();
		
		// form layout
		new_txt = new PasswordField("New Password");
		new_txt.setWidth("15em");
		new_txt.focus();
		
		confirm_txt = new PasswordField("Confirm Password");
		confirm_txt.setWidth("15em");
		
		FormLayout form = new FormLayout();
		form.setSizeUndefined();
		form.addComponent(new_txt);
		form.addComponent(confirm_txt);
		
		// content layout
		info = new Label();
		info.setSizeUndefined();
		info.setValue("Please fill in all fields below");
		
		Label gap = new Label();
		gap.setHeight("1em");
		
		submit = new Button("Submit");
		submit.setDescription("Save changes!");
		submit.setSizeFull();
		submit.setStyleName("primary");
		
		cancel = new Button("Cancel");
		cancel.setDescription("Return to login screen!");
		cancel.setSizeFull();
		
		VerticalLayout content = new VerticalLayout();
		content.setSizeUndefined();
		content.setSpacing(true);
		content.setMargin(true);
		content.addComponent(info);
		content.setComponentAlignment(info, Alignment.MIDDLE_CENTER);
		content.addComponent(form);
		content.addComponent(gap);
		content.addComponent(submit);
		content.addComponent(cancel);		
		
		// add 'content' to 'main frame'
		pane.setContent(content);

		// password rules layout
		TextArea help_txt = new TextArea("Password Rules");
		help_txt.setRows(7);
		help_txt.setWidth("40em");
		help_txt.setValue(passwordRules());
		help_txt.setReadOnly(true);
		
		Label help_gap = new Label();
		help_gap.setHeight("5em");
		
		// root layout
		this.setMargin(true);
		this.addComponent(pane);
		this.setComponentAlignment(pane, Alignment.TOP_CENTER);
		this.addComponent(help_gap);
		this.addComponent(help_txt);
		this.setComponentAlignment(help_txt, Alignment.MIDDLE_CENTER);		
		
		
		//
		// user interaction
		//
		submit.addClickListener(event -> handleSubmit(event));
		cancel.addClickListener(event -> handleCancel(event));
	}
	
	private void handleSubmit(ClickEvent event)
	{
		final String pw = new_txt.getValue().trim();
		final String pw_con = confirm_txt.getValue().trim();
		
		if(pw.isEmpty() || pw_con.isEmpty())
		{
			info.setValue("One or more fields are empty");
		}
		else if(!iv.isPasswordPolicy(pw, emp.getUsername(), emp.getFirst_name(), emp.getLast_name()) || !pw.equals(pw_con))
		{
			info.setValue("Invalid password entry, see password rules below");
		}
		else if(pw.equals(emp.getPassword()))
		{
			info.setValue("Password already in use");
		}
		else
		{
			try {
				// SQL statment to update password
				String update = "update employee" +
								" set password=" + 
								"'" + pw + "'" + 
								" where id=" + emp.getId();
			
				// update database
				db.getStatement().executeUpdate(update);
		
				// debug code
				System.out.println(emp.getUsername() + " password changed");
				
				UI.getCurrent().setContent(new LoginView());
				
			} catch (SQLException e) {
				e.printStackTrace();
			}
		}

	}
	
	private void handleCancel(ClickEvent event)
	{
		UI.getCurrent().setContent(new LoginView());
	}
	
	private String passwordRules()
	{
		return "1) Cannot contain user's login name or any part of the user's full name\n" +
				"2) Must be at least 6 characters in length\n" +
				"3) Must contain at least 1 character from each group:\n" +
				"\t-Uppercase (A to Z)\n" +
				"\t-Lowercase (a to z)\n" +
				"\t-Number (0 to 9)";
	}
	
}
