package com.bgna.app;

import com.vaadin.ui.Alignment;
import com.vaadin.ui.Button;
import com.vaadin.ui.Label;
import com.vaadin.ui.Panel;
import com.vaadin.ui.UI;
import com.vaadin.ui.VerticalLayout;
import com.vaadin.ui.Button.ClickEvent;

@SuppressWarnings("serial")
public class AccountReg2View extends VerticalLayout {

	private Button back;
	private Label info;
	private Label info2;
	
	public AccountReg2View()
	{
		buildView();
	}
	
	private void buildView()
	{
		// main frame
		Panel pane = new Panel("Registration");
		pane.setSizeUndefined();	
		
		// content layout
		info = new Label("You have successfully registered.");
		info.setSizeUndefined();
		
		info2 = new Label("Please click on the button below to return to the login screen.");
		info2.setSizeUndefined();

		Label gap = new Label();
		gap.setHeight("1em");
		
		back = new Button("Back");
		back.setDescription("Return to login screen!");
		back.setSizeFull();
		back.setStyleName("primary");
		
		VerticalLayout content = new VerticalLayout();
		content.setSizeUndefined();
		content.setSpacing(true);
		content.setMargin(true);
		content.addComponent(info);
		content.setComponentAlignment(info, Alignment.MIDDLE_CENTER);
		content.addComponent(info2);
		content.setComponentAlignment(info2, Alignment.MIDDLE_CENTER);
		content.addComponent(gap);
		content.addComponent(back);
		
		// add 'content' to 'main frame'
		pane.setContent(content);

		// root layout
		this.setMargin(true);
		this.addComponent(pane);
		this.setComponentAlignment(pane, Alignment.TOP_CENTER);
		
		
		//
		// user interaction
		//
		back.addClickListener(event -> handleBack(event));
	}
	
	private void handleBack(ClickEvent event)
	{
		UI.getCurrent().setContent(new LoginView());
	}

}
