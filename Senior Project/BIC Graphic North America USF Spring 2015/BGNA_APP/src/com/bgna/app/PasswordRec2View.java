package com.bgna.app;

import com.vaadin.ui.Alignment;
import com.vaadin.ui.Button;
import com.vaadin.ui.FormLayout;
import com.vaadin.ui.Label;
import com.vaadin.ui.NativeSelect;
import com.vaadin.ui.Panel;
import com.vaadin.ui.TextArea;
import com.vaadin.ui.UI;
import com.vaadin.ui.VerticalLayout;
import com.vaadin.ui.Button.ClickEvent;

@SuppressWarnings("serial")
public class PasswordRec2View extends VerticalLayout {
	
	User emp;
	
	private Button submit;
	private Button cancel;
	private Label info;
	private NativeSelect mnth_sel;
	private NativeSelect day_sel;
	private TextArea question_txt;
	private TextArea ans_txt;
	
	public PasswordRec2View(User emp)
	{
		this.emp = emp;
		buildView();
	}
	
	private void buildView()
	{
		// main frame
		Panel pane = new Panel("Create New Password");
		pane.setSizeUndefined();
		
		// form layout
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
		form.addComponent(mnth_sel);
		form.addComponent(day_sel);
		
		// content layout
		info = new Label();
		info.setSizeUndefined();
		info.setValue("Please fill in all fields below");
		
		question_txt = new TextArea("Security Question");		
		question_txt.setValue(emp.getRandomQuestion());	// query user for security question
		question_txt.setReadOnly(true);
		question_txt.setRows(2);
		question_txt.setWidth("20em");
		
		ans_txt = new TextArea("Answer");
		ans_txt.setRows(2);
		ans_txt.setWidth("20em");
		
		Label gap = new Label();
		gap.setHeight("1em");
		
		submit = new Button("Continue");
		submit.setDescription("Continue password creation!");
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
		content.addComponent(question_txt);
		content.addComponent(ans_txt);
		content.addComponent(gap);
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
		final String mnth = mnth_sel.getValue().toString();
		final String day = day_sel.getValue().toString();
		final String answer = ans_txt.getValue().toString().trim();
		
		if(answer.isEmpty())
		{
			info.setValue("Answer is empty");
		}
		else if(!mnth.equals(emp.getBirth_month()) || !day.equals(emp.getBirth_day()))
		{
			info.setValue("Incorrect birth month and day for user");
		}
		else if(!isAnswerCorrect())
		{
			info.setValue("Incorrect answer to security question");
		}
		else
			UI.getCurrent().setContent(new PasswordRec3View(emp));
	}
	
	private void handleCancel(ClickEvent event)
	{
		UI.getCurrent().setContent(new LoginView());
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
