package com.bgna.app;

import java.sql.SQLException;

import com.vaadin.ui.Alignment;
import com.vaadin.ui.Button;
import com.vaadin.ui.Button.ClickEvent;
import com.vaadin.ui.FormLayout;
import com.vaadin.ui.Label;
import com.vaadin.ui.NativeSelect;
import com.vaadin.ui.Panel;
import com.vaadin.ui.PasswordField;
import com.vaadin.ui.TextArea;
import com.vaadin.ui.UI;
import com.vaadin.ui.VerticalLayout;

@SuppressWarnings("serial")
public class AccountServiceView extends VerticalLayout {

	DatabaseHelper db;
	InputValidate iv;
	User emp;
	
	private Button submit;
	private Button cancel;
	private Label info;
	private NativeSelect mnth_sel;
	private NativeSelect day_sel;
	private TextArea question_txt;
	private TextArea ans_txt;
	private PasswordField new_txt;
	private PasswordField confirm_txt;
	
	public AccountServiceView(User emp)
	{
		this.db = new DatabaseHelper();
		this.iv = new InputValidate();
		this.emp = emp;
		
		// debug code
		System.out.println("Account service user: " + emp.getUsername());
		
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
		
		FormLayout form = new FormLayout();
		form.setSizeUndefined();
		form.addComponent(new_txt);
		form.addComponent(confirm_txt);
		form.addComponent(mnth_sel);
		form.addComponent(day_sel);
		
		// content layout
		info = new Label();
		info.setSizeUndefined();
		info.setValue("Please fill in all fields below");
		
		question_txt = new TextArea("Security Question");		
		question_txt.setValue(emp.getRandomQuestion());	// query user for random security question	
		question_txt.setReadOnly(true);
		question_txt.setRows(2);
		question_txt.setSizeFull();
		
		ans_txt = new TextArea("Answer");
		ans_txt.setRows(2);
		ans_txt.setSizeFull();
		
		Label gap = new Label();
		gap.setHeight("1em");
		
		submit = new Button("Submit");
		submit.setDescription("Save changes!");
		submit.setSizeFull();
		submit.setStyleName("primary");
		
		cancel = new Button("Cancel");
		cancel.setDescription("Quit without saving changes!");
		cancel.setSizeFull();
		
		VerticalLayout content = new VerticalLayout();
		content.setSizeUndefined();
		content.setSpacing(true);
		content.setMargin(true);
		content.addComponent(info);
		content.setComponentAlignment(info, Alignment.MIDDLE_CENTER);
		content.addComponent(form);
		content.addComponent(question_txt);
		content.addComponent(ans_txt);
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
		final String ans = ans_txt.getValue().trim();
		final String mnth = mnth_sel.getValue().toString();
		final String day = day_sel.getValue().toString();
		
		final String[] items = {pw,pw_con,ans};
		
		if(!iv.noneEmpty(items))
		{
			info.setValue("One or more fields are empty");
		}
		else if(!iv.isPasswordPolicy(pw, emp.getUsername(), emp.getFirst_name(), emp.getLast_name()) || !pw.equals(pw_con))
		{
			info.setValue("Invalid password entry, see password rules below");
		}
		else if(!mnth.equalsIgnoreCase(emp.getBirth_month()) || !day.equalsIgnoreCase(emp.getBirth_day()))
		{
			info.setValue("Incorrect birth month and day");
		}
		else if(!isAnswerCorrect())
		{
			info.setValue("Incorrect answer to security question");
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
		// check for supervisor or normal employee
		if(emp.getRole().equalsIgnoreCase("super"))
			UI.getCurrent().setContent(new SupervisorView(emp));
		else if (emp.getRole().equalsIgnoreCase("user"))
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

	private boolean isAnswerCorrect()
	{
		if(question_txt.getValue().equals(emp.getSecurity_q1()))
		{
			if(ans_txt.getValue().trim().equalsIgnoreCase(emp.getSecurity_ans1()))
				return true;
		}
		else if(question_txt.getValue().equals(emp.getSecurity_q2()))
		{
			if(ans_txt.getValue().trim().equalsIgnoreCase(emp.getSecurity_ans2()))
				return true;
		}
		else if(question_txt.getValue().equals(emp.getSecurity_q3()))
		{
			if(ans_txt.getValue().trim().equalsIgnoreCase(emp.getSecurity_ans3()))
				return true;
		}
		
		return false;
	}

}
