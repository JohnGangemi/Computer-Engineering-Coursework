package com.bgna.app;

import java.sql.ResultSet;
import java.sql.SQLException;

import com.vaadin.ui.Alignment;
import com.vaadin.ui.Button;
import com.vaadin.ui.FormLayout;
import com.vaadin.ui.Label;
import com.vaadin.ui.Panel;
import com.vaadin.ui.TextField;
import com.vaadin.ui.UI;
import com.vaadin.ui.VerticalLayout;
import com.vaadin.ui.Button.ClickEvent;

@SuppressWarnings("serial")
public class PasswordRec1View extends VerticalLayout {
	
	DatabaseHelper db;
	User emp;
	
	private Button submit;
	private Button cancel;
	private TextField usrname_txt;
	private Label info;
	
	public PasswordRec1View()
	{
		db = new DatabaseHelper();
		emp = new User();
		buildView();
	}
	
	private void buildView()
	{
		// main frame
		Panel pane = new Panel("Create New Password");
		pane.setSizeUndefined();
		
		// content layout		
		usrname_txt = new TextField("Username");
		usrname_txt.setWidth("15em");
		usrname_txt.focus();
		
		FormLayout form = new FormLayout();
		form.setSizeUndefined();
		form.addComponent(usrname_txt);

		submit = new Button("Continue");
		submit.setDescription("Continue password creation!");
		submit.setSizeFull();
		submit.setStyleName("primary");
		
		cancel = new Button("Cancel");
		cancel.setDescription("Return to login screen!");
		cancel.setSizeFull();
		
		info = new Label();
		info.setValue("Please enter a username");
		info.setSizeUndefined();

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
		final String un = usrname_txt.getValue().trim();
		
		if(un.isEmpty())
			info.setValue("Username is empty");
		else
		{
		
			final String bg_un = "bg" + un;
			boolean valid = false;
			
			try {
				// validate against database
				ResultSet rs = db.getStatement().executeQuery("select * from employee");
				
				while(rs.next())
				{
					if(bg_un.equalsIgnoreCase(rs.getString("username")))
					{
						emp.setAll(rs);
						valid = true;
					}
				}
				
				// release JDBC resources consumed by 'rs'
				rs.close();
				
				if(valid)
				{
					//debug code
					System.out.println("Username accepted for " + emp.getUsername());
					
					UI.getCurrent().setContent(new PasswordRec2View(emp));
				}
				else
					info.setValue("Invalid username");
					
			} catch (SQLException e) {
				e.printStackTrace();
			}
			
		}

	}
	
	private void handleCancel(ClickEvent event)
	{
		UI.getCurrent().setContent(new LoginView());
	}

}
