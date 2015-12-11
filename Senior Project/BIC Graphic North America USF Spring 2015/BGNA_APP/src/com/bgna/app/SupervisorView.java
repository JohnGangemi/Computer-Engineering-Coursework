package com.bgna.app;

import com.vaadin.ui.Alignment;
import com.vaadin.ui.Button;
import com.vaadin.ui.Label;
import com.vaadin.ui.Panel;
import com.vaadin.ui.UI;
import com.vaadin.ui.VerticalLayout;
import com.vaadin.ui.Button.ClickEvent;

@SuppressWarnings("serial")
public class SupervisorView extends VerticalLayout {

	User emp;
	
	private Label employee_lbl;
	private Label supervisor_lbl;
	private Button update_btn;
	private Button create_btn;
	private Button passwrd_btn;
	private Button cancel_btn;
	
	public SupervisorView(User emp)
	{
		this.emp = emp;
		
		// debug code
		System.out.println("Supervisor user: " + emp.getUsername());
				
		buildView();
	}
	
	private void buildView()
	{
		// main frame
		Panel pane = new Panel("Manage Accounts");
		pane.setWidth("25em");	
		
		// content layout
		employee_lbl = new Label("Employee");
		employee_lbl.setSizeFull();

		update_btn = new Button("Update Account");
		update_btn.setDescription("Update an existing account!");
		update_btn.setSizeFull();
		
		create_btn = new Button("Create Account");
		create_btn.setDescription("Create a new account!");
		create_btn.setSizeFull();
			
		supervisor_lbl = new Label("Supervisor");
		supervisor_lbl.setSizeFull();
		
		passwrd_btn = new Button("Change Password");
		passwrd_btn.setDescription("Change your password!");
		passwrd_btn.setSizeFull();
		
		cancel_btn = new Button("Cancel");
		cancel_btn.setDescription("Return to login screen!");
		cancel_btn.setSizeFull();
		
		Label gap = new Label();
		gap.setHeight("1em");
		
		Label gap2 = new Label();
		gap2.setHeight("1em");
		
		Label gap3 = new Label();
		gap3.setHeight("1em");
		
		VerticalLayout content = new VerticalLayout();
		content.setSizeFull();
		content.setSpacing(true);
		content.setMargin(true);
		content.addComponent(gap);
		content.addComponent(employee_lbl);
		content.addComponent(update_btn);
		content.addComponent(create_btn);
		content.addComponent(gap2);
		content.addComponent(supervisor_lbl);
		content.addComponent(passwrd_btn);
		content.addComponent(gap3);
		content.addComponent(cancel_btn);
		
		// add 'content' to 'main frame'
		pane.setContent(content);

		// root layout
		this.setMargin(true);
		this.addComponent(pane);
		this.setComponentAlignment(pane, Alignment.TOP_CENTER);
		
		
		//
		// user interaction
		//
		update_btn.addClickListener(event -> handleUpdate(event));
		create_btn.addClickListener(event -> handleCreate(event));
		passwrd_btn.addClickListener(event -> handleChangePassword(event));
		cancel_btn.addClickListener(event -> handleCancel(event));		
	}
	
	private void handleUpdate(ClickEvent event)
	{
		UI.getCurrent().setContent(new AccountUpdateView(emp));
	}
	
	private void handleCreate(ClickEvent event)
	{
		UI.getCurrent().setContent(new AccountCreateView(emp));
	}
	
	private void handleChangePassword(ClickEvent event)
	{
		UI.getCurrent().setContent(new AccountServiceView(emp));
	}
	
	private void handleCancel(ClickEvent event)
	{
		UI.getCurrent().setContent(new LoginView());
	}
	
}
