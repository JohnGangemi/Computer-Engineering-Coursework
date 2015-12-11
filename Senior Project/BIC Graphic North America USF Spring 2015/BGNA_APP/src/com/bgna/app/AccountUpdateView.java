package com.bgna.app;

import java.sql.ResultSet;
import java.sql.SQLException;

import com.vaadin.ui.Alignment;
import com.vaadin.ui.Button;
import com.vaadin.ui.FormLayout;
import com.vaadin.ui.Label;
import com.vaadin.ui.NativeSelect;
import com.vaadin.ui.Panel;
import com.vaadin.ui.PasswordField;
import com.vaadin.ui.TextArea;
import com.vaadin.ui.TextField;
import com.vaadin.ui.UI;
import com.vaadin.ui.VerticalLayout;
import com.vaadin.ui.Button.ClickEvent;

@SuppressWarnings("serial")
public class AccountUpdateView extends VerticalLayout {

	DatabaseHelper db;
	InputValidate iv;
	User emp;	
	
	private Button submit;
	private Button cancel;
	private Label info;
	private TextField usrname_txt;
	private TextField fname_txt;
	private TextField lname_txt;
	private PasswordField passwrd_txt;
	private NativeSelect role_sel;
	
	public AccountUpdateView(User emp)
	{
		db = new DatabaseHelper();
		iv = new InputValidate();
		this.emp = emp;
		buildView();
	}
	
	private void buildView()
	{
		// main frame
		Panel pane = new Panel("Update Existing Account");
		pane.setSizeUndefined();
		
		// form layout
		usrname_txt = new TextField("Find by username");
		usrname_txt.setWidth("15em");
		usrname_txt.focus();
		
		Label gap = new Label();
		gap.setHeight("1em");
		
		fname_txt = new TextField("First Name");
		fname_txt.setWidth("15em");
		
		lname_txt = new TextField("Last Name");
		lname_txt.setWidth("15em");
		
		passwrd_txt = new PasswordField("New Password");
		passwrd_txt.setWidth("15em");
		
		role_sel = new NativeSelect("System Role");
		role_sel.addItems("system user", "supervisor");
		role_sel.setValue("system user");
		role_sel.setMultiSelect(false);
		role_sel.setNullSelectionAllowed(false);
		role_sel.setImmediate(true);
		//role_sel.setWidth("15em");
		
		FormLayout form = new FormLayout();
		form.setSizeUndefined();
		form.addComponent(usrname_txt);
		form.addComponent(gap);
		form.addComponent(fname_txt);
		form.addComponent(lname_txt);
		form.addComponent(passwrd_txt);
		form.addComponent(role_sel);
		
		// content layout
		info = new Label();
		info.setSizeUndefined();
		info.setValue("Please fill in all fields below");
		
		submit = new Button("Submit");
		submit.setDescription("Save changes!");
		submit.setSizeFull();
		submit.setStyleName("primary");
		
		cancel = new Button("Cancel");
		cancel.setDescription("Return to supervisor screen!");
		cancel.setSizeFull();

		VerticalLayout content = new VerticalLayout();
		content.setSizeUndefined();
		content.setSpacing(true);
		content.setMargin(true);
		content.addComponent(info);
		content.setComponentAlignment(info, Alignment.MIDDLE_CENTER);
		content.addComponent(form);
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
		final String un = usrname_txt.getValue().trim();
		final String fname = fname_txt.getValue().trim();
		final String lname = lname_txt.getValue().trim();
		final String pw = passwrd_txt.getValue().trim();
		final String role = extractRole(role_sel.getValue().toString());
		
		String[] items = {fname,lname,un,pw};
		
		if(!iv.noneEmpty(items))
			info.setValue("One or more fields are empty");
		else
		{
			final String bg_un = "bg" + un;
			String err_msg = null;
			boolean valid = false;
			int userID = 0;

			try {
				ResultSet rs = db.getStatement().executeQuery("select * from employee");
				
				while(rs.next())
				{
					if(bg_un.equalsIgnoreCase(rs.getString("username")))
					{
						if(!iv.isPasswordPolicy(pw, un, rs.getString("first_name"), rs.getString("last_name")))
							err_msg = "Invalid password entry, see password rules below";
						else if(pw.equals(rs.getString("password")))
							err_msg = "Password already in use";
						else
						{
							userID = rs.getInt("id");
							valid = true;
						}
						
						break;
					}
				}
				
				// release JDBC resources consumed by ResultSet 'rs'
				rs.close();
				
				if(valid)
				{
					// SQL statment to update password
					String update = "update employee" +
									" set first_name=" + "'" + fname.toUpperCase() + "' ," + 
									" last_name=" + "'" + lname.toUpperCase() + "' ," +
									" password=" + "'" + pw + "' ," +
									" role=" + "'" + role.toLowerCase() + "'" +
									" where id=" + userID;
				
					// update database
					db.getStatement().executeUpdate(update);
			
					// debug code
					System.out.println("User " + bg_un + " updated");
					
					UI.getCurrent().setContent(new SupervisorView(emp));
				}
				else
				{
					if(err_msg == null)
						info.setValue("Could not find account by username");
					else
						info.setValue(err_msg);
				}
				
			} catch (SQLException e) {
				e.printStackTrace();
			}
			
		}
		
	}
	
	private void handleCancel(ClickEvent event)
	{
		UI.getCurrent().setContent(new SupervisorView(emp));
	}
	
	private String extractRole(String role)
	{
		if(role.equalsIgnoreCase("system user"))
			return "user";
		else if(role.equalsIgnoreCase("supervisor"))
			return "super";
		else
			return "undefined";
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
