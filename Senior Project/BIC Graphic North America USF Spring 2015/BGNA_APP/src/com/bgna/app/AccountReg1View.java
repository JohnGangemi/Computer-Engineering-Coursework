package com.bgna.app;

import java.sql.ResultSet;
import java.sql.SQLException;

import com.vaadin.ui.Alignment;
import com.vaadin.ui.Button;
import com.vaadin.ui.FormLayout;
import com.vaadin.ui.HorizontalLayout;
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
public class AccountReg1View extends VerticalLayout {
	
	DatabaseHelper db;
	InputValidate iv;
	
	final private int upper_bound = 9999999;
	final private int lower_bound = 1000000;
	
	private Button submit;
	private Button cancel;
	private Label info;
	private NativeSelect mnth_sel;
	private NativeSelect day_sel;
	private TextField fname_txt;
	private TextField lname_txt;
	private TextField usrname_txt;
	private PasswordField passwrd_txt;
	private PasswordField confirm_txt;
	private TextField code_txt;
	private NativeSelect sq1_sel;
	private TextArea ans1_txt;
	private NativeSelect sq2_sel;
	private TextArea ans2_txt;
	private NativeSelect sq3_sel;
	private TextArea ans3_txt;
	
	public AccountReg1View()
	{
		db = new DatabaseHelper();
		iv = new InputValidate();
		buildView();
	}
	
	private void buildView()
	{
		// main frame
		Panel pane = new Panel("Registration");
		pane.setWidth("50em");
		
		/////////////////////////////////////////////////////////////////////////
		// form 1 layout
		fname_txt = new TextField("First Name");
		fname_txt.focus();
		
		lname_txt = new TextField("Last Name");
		
		mnth_sel = new NativeSelect("Birth Month");
		mnth_sel.addItems("January","February","March","April","May","June","July","August","September","October","November","December");
		mnth_sel.setValue("January");
		mnth_sel.setMultiSelect(false);
		mnth_sel.setNullSelectionAllowed(false);
		mnth_sel.setImmediate(true);
		
		day_sel = new NativeSelect("Birth Day");
		for(int i = 0; i < 31; i++)
			day_sel.addItem(i + 1);
		day_sel.setValue(1);
		day_sel.setMultiSelect(false);
		day_sel.setNullSelectionAllowed(false);
		day_sel.setImmediate(true);
		
		FormLayout form1 = new FormLayout();
		form1.setSizeUndefined();
		form1.addComponent(fname_txt);
		form1.addComponent(lname_txt);
		form1.addComponent(mnth_sel);
		form1.addComponent(day_sel);
		
		// form 2 layout
		code_txt = new TextField("Registration Code");
		
		usrname_txt = new TextField("Username");
		
		passwrd_txt = new PasswordField("Password");
		
		confirm_txt = new PasswordField("Confirm Password");
		
		FormLayout form2 = new FormLayout();
		form2.setSizeUndefined();
		form2.addComponent(code_txt);
		form2.addComponent(usrname_txt);
		form2.addComponent(passwrd_txt);
		form2.addComponent(confirm_txt);
		
		// horizontal layout form1 and form2
		HorizontalLayout forms = new HorizontalLayout();
		forms.setSizeFull();
		forms.setSpacing(true);
		forms.addComponent(form1);
		forms.addComponent(form2);
		/////////////////////////////////////////////////////////////////////////
		
		// layout questions and answers
		sq1_sel = new NativeSelect("Security Question 1");
		sq1_sel.addItems("What is your favorite food?",
				"What is your favorite movie?",
				"What is your favorite book?",
				"Who is your favorite actor?");
		sq1_sel.setValue("What is your favorite food?");
		sq1_sel.setMultiSelect(false);
		sq1_sel.setNullSelectionAllowed(false);
		sq1_sel.setImmediate(true);
		
		ans1_txt = new TextArea("Answer 1");
		ans1_txt.setRows(2);
		ans1_txt.setSizeFull();

		HorizontalLayout row1 = new HorizontalLayout();
		row1.setSizeFull();
		row1.setSpacing(true);
		row1.addComponent(sq1_sel);
		row1.addComponent(ans1_txt);
		
		
		sq2_sel = new NativeSelect("Security Question 2");
		sq2_sel.addItems("Maiden name of your mother?",
				"Middle name of your father?",
				"Maiden name of your grandmother?",
				"Name of your grandfather?");
		sq2_sel.setValue("Maiden name of your mother?");
		sq2_sel.setMultiSelect(false);
		sq2_sel.setNullSelectionAllowed(false);
		sq2_sel.setImmediate(true);
		
		ans2_txt = new TextArea("Answer 2");
		ans2_txt.setRows(2);
		ans2_txt.setSizeFull();

		HorizontalLayout row2 = new HorizontalLayout();
		row2.setSizeFull();
		row2.setSpacing(true);
		row2.addComponent(sq2_sel);
		row2.addComponent(ans2_txt);
		
		
		sq3_sel = new NativeSelect("Security Question 3");
		sq3_sel.addItems("In what city were you born?",
				"What was your highschool mascot?",
				"What make was your first car?",
				"What was the name of your first pet?");
		sq3_sel.setValue("In what city were you born?");
		sq3_sel.setMultiSelect(false);
		sq3_sel.setNullSelectionAllowed(false);
		sq3_sel.setImmediate(true);
		
		ans3_txt = new TextArea("Answer 3");
		ans3_txt.setRows(2);
		ans3_txt.setSizeFull();

		HorizontalLayout row3 = new HorizontalLayout();
		row3.setSizeFull();
		row3.setSpacing(true);
		row3.addComponent(sq3_sel);
		row3.addComponent(ans3_txt);
		/////////////////////////////////////////////////////////////////////////
		
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
		content.setSizeFull();
		content.setSpacing(true);
		content.setMargin(true);
		content.addComponent(info);
		content.setComponentAlignment(info, Alignment.MIDDLE_CENTER);
		content.addComponent(forms);
		content.addComponent(row1);
		content.addComponent(row2);
		content.addComponent(row3);
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
		final String fname = fname_txt.getValue().trim();
		final String lname = lname_txt.getValue().trim();
		final String mnth = mnth_sel.getValue().toString();
		final String day = day_sel.getValue().toString();
		final String code = code_txt.getValue().trim();
		final String un = usrname_txt.getValue().trim();
		final String pw = passwrd_txt.getValue().trim();
		final String pw_con = confirm_txt.getValue().trim();
		final String q1 = sq1_sel.getValue().toString();
		final String q2 = sq2_sel.getValue().toString();
		final String q3 = sq3_sel.getValue().toString();
		final String a1 = ans1_txt.getValue().trim();
		final String a2 = ans2_txt.getValue().trim();
		final String a3 = ans3_txt.getValue().trim();
		
		final String[] items = {fname,lname,code,un,pw,pw_con,a1,a2,a3};

		// validate input
		if(!iv.noneEmpty(items))
		{
			info.setValue("One or more fields are empty");
		}
		else if(!iv.isBirthDateValid(mnth, day))
		{
			info.setValue("Invalid combination of birth month and day");
		}
		else if (!code.matches("[0-9]+") || (Integer.parseInt(code) < lower_bound || Integer.parseInt(code) > upper_bound))
		{
			info.setValue("Registration code must be 7 numbers");
		}
		else if(!iv.isPasswordPolicy(pw, un, fname, lname) || !pw.equals(pw_con))
		{
			info.setValue("Invalid password entry, see password rules below");
		}
		else if(iv.isSpecialChars(a1) || iv.isSpecialChars(a2) || iv.isSpecialChars(a3))
		{
			info.setValue("Answers can have letters and/or numbers only");
		}
		else
		{
			final String bg_un = "bg" + un;
			boolean user_valid = false;
			boolean username_exists = false;
			int userID = 0; // primary key for table 'employee'
			
			try {			
				// validate against database
				ResultSet rs = db.getStatement().executeQuery("select * from employee");
				
				while(rs.next())
				{
					// check first name, last name, reg code, and registered columns in database
					// against user input
					if(fname.equalsIgnoreCase(rs.getString("first_name")) 
							&& lname.equalsIgnoreCase(rs.getString("last_name")) 
							&& code.equalsIgnoreCase(rs.getString("reg_code"))
							&& rs.getInt("registered") < 1)
					{
						user_valid = true;
						userID = rs.getInt("id");
					}
					
					// check if username is taken
					if(bg_un.equalsIgnoreCase(rs.getString("username")))
						username_exists = true;
				}
				
				// release JDBC resources consumed by 'rs'
				rs.close();
				
				if(user_valid && !username_exists)
				{
					// SQL statment to update employee
					String update = "update employee" +
									" set username=" + "'" + bg_un + "'" + "," +
									" password=" + "'" + pw + "'" + "," +
									" birth_month=" + "'" + mnth + "'" + "," +
									" birth_day=" + "'" + day + "'" + "," +
									" question1=" + "'" + q1 + "'" + "," +
									" question2=" + "'" + q2 + "'" + "," +
									" question3=" + "'" + q3 + "'" + "," +
									" answer1=" + "'" + a1 + "'" + "," +
									" answer2=" + "'" + a2 + "'" + "," +
									" answer3=" + "'" + a3 + "'" + "," +
									
									// set 'registered' > 0 to prevent user re-registering
									" registered=" + 1 + 
									" where id=" + userID;
				
					// update database
					db.getStatement().executeUpdate(update);
			
					// debug code
					System.out.println("User has registered, check database table -> employee");
					
					UI.getCurrent().setContent(new AccountReg2View());
				}
				else if(user_valid && username_exists)
					info.setValue("Username already exists");
				else
					info.setValue("Incorrect name, registration code, or account already active");
				
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
