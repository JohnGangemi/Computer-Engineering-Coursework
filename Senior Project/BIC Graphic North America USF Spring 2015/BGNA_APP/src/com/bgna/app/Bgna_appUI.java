package com.bgna.app;

import javax.servlet.annotation.WebServlet;

import com.vaadin.annotations.Theme;
import com.vaadin.annotations.VaadinServletConfiguration;
import com.vaadin.server.Page;
import com.vaadin.server.VaadinRequest;
import com.vaadin.server.VaadinServlet;
import com.vaadin.ui.UI;

@SuppressWarnings("serial")
@Theme("bgna_app")
public class Bgna_appUI extends UI {

	// server-side stuff <DO NOT REMOVE>
	@WebServlet(value = "/*", asyncSupported = true)
	@VaadinServletConfiguration(productionMode = false, ui = Bgna_appUI.class)
	public static class Servlet extends VaadinServlet {
	}

	// UI set-up
	@Override
	protected void init(VaadinRequest request) 
	{
		Page.getCurrent().setTitle("BIC Graphic North America");
		this.setContent(new LoginView());
	}

}