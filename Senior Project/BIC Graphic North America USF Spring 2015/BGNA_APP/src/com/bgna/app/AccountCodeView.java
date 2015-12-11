package com.bgna.app;

import com.vaadin.ui.Alignment;
import com.vaadin.ui.Button;
import com.vaadin.ui.Label;
import com.vaadin.ui.Panel;
import com.vaadin.ui.TextArea;
import com.vaadin.ui.TextField;
import com.vaadin.ui.UI;
import com.vaadin.ui.VerticalLayout;
import com.vaadin.ui.Button.ClickEvent;

@SuppressWarnings("serial")
public class AccountCodeView extends VerticalLayout {
	
	User emp;
	
	private int code;
	private Button back;
	private TextField code_txt;
	
	public AccountCodeView(User emp, int code)
	{
		this.emp = emp;
		this.code = code;
		buildView();
	}
	
	private void buildView()
	{
		// main frame
		Panel pane = new Panel("Print From Browser");
		pane.setWidth("600px");	
		
		// content layout
		TextArea instr = new TextArea("Instructions");
		instr.setRows(8);
		instr.setSizeFull();
		instr.setValue("Please use the registration code below to register"
				+ " your account by clicking the New User? button"
				+ " on the login screen.\n"
				+ "\nIf you do not see the login screen press the refresh"
				+ " icon in the top left area of the main window.\n");
		instr.setReadOnly(true);
		
		Label gap = new Label();
		gap.setHeight("1em");
		
		code_txt = new TextField("Registration Code");
		code_txt.setValue(Integer.toString(code));
		code_txt.setReadOnly(true);
		code_txt.setWidth("10em");
		code_txt.setStyleName("align-center");
		
		back = new Button("Back");
		back.setDescription("Return to supervisor screen!");
		back.setSizeFull();
		back.setStyleName("primary");
		
		VerticalLayout content = new VerticalLayout();
		content.setSizeFull();
		content.setSpacing(true);
		content.setMargin(true);
		content.addComponent(instr);
		content.setComponentAlignment(instr, Alignment.MIDDLE_CENTER);
		content.addComponent(code_txt);
		content.setComponentAlignment(code_txt, Alignment.MIDDLE_CENTER);
		content.addComponent(gap);
		content.addComponent(back);
		content.setComponentAlignment(back, Alignment.MIDDLE_CENTER);
		
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
		UI.getCurrent().setContent(new SupervisorView(emp));
	}

}
