package com.bgna.app;

import java.sql.SQLException;
import java.util.Random;

import com.vaadin.ui.Alignment;
import com.vaadin.ui.Button;
import com.vaadin.ui.FormLayout;
import com.vaadin.ui.Label;
import com.vaadin.ui.NativeSelect;
import com.vaadin.ui.Panel;
import com.vaadin.ui.TextField;
import com.vaadin.ui.UI;
import com.vaadin.ui.VerticalLayout;
import com.vaadin.ui.Button.ClickEvent;

@SuppressWarnings("serial")
public class AccountCreateView extends VerticalLayout {

	DatabaseHelper db;
	InputValidate iv;
	User emp;	
	
	final private int upper_bound = 9999999;
	final private int lower_bound = 1000000;
	
	private Button submit;
	private Button cancel;
	private Label info;
	private TextField fname_txt;
	private TextField lname_txt;
	private TextField depart_txt;
	private NativeSelect role_sel;
	
	public AccountCreateView(User emp)
	{
		db = new DatabaseHelper();
		iv = new InputValidate();
		this.emp = emp;
		buildView();
	}
	
	private void buildView()
	{
		// main frame
		Panel pane = new Panel("Create New Account");
		pane.setSizeUndefined();
		
		// form layout
		fname_txt = new TextField("First Name");
		fname_txt.setWidth("15em");
		fname_txt.focus();
		
		lname_txt = new TextField("Last Name");
		lname_txt.setWidth("15em");
		
		depart_txt = new TextField("Department");
		depart_txt.setWidth("15em");
		
		role_sel = new NativeSelect("System Role");
		role_sel.addItems("system user", "supervisor");
		role_sel.setValue("system user");
		role_sel.setMultiSelect(false);
		role_sel.setNullSelectionAllowed(false);
		role_sel.setImmediate(true);
		//role_sel.setWidth("15em");
		
		FormLayout form = new FormLayout();
		form.setSizeUndefined();
		form.addComponent(fname_txt);
		form.addComponent(lname_txt);
		form.addComponent(depart_txt);
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

		// root layout
		this.setMargin(true);
		this.addComponent(pane);
		this.setComponentAlignment(pane, Alignment.TOP_CENTER);
		
		
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
		final String department = depart_txt.getValue().trim();
		final String role = extractRole(role_sel.getValue().toString());
		
		String[] items = {fname,lname,department};
		
		if(!iv.noneEmpty(items))
			info.setValue("One or more fields are empty");
		else
		{
			final int code = generateRegCode();
			
			try {
				// SQL statment to update password
				String update = "insert into employee" +
								"(first_name, last_name, reg_code, registered, department, role) values" +					
								" ('" + fname.toUpperCase() + "' ," + 
								" '" + lname.toUpperCase() + "' ," +
								" '" + code + "' ," +
								
								// set user as unregistered
								" '" + 0 + "' ," +
								
								" '" + department + "' ," +
								" '" + role.toLowerCase() + "')";
			
				// update database
				db.getStatement().executeUpdate(update);
	
				// debug code
				System.out.println("New user created in database");
				
				UI.getCurrent().setContent(new AccountCodeView(emp, code));
			
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

	private int generateRegCode() {
		Random rand = new Random();	
		return rand.nextInt((upper_bound - lower_bound) + 1) + lower_bound;
	}
	
}
