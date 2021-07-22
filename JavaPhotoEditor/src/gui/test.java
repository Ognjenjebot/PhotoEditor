package gui;
import java.awt.*;
import java.awt.event.*;
/*
public class test extends Frame {
	private class Platno extends Canvas{
		public void paint(Graphics g) {
			int sirina = getWidth(), visina = getHeight();
			g.drawLine(0, 0, sirina - 1, visina - 1);
			g.translate(sirina - 1 - sirina / 3, 0);
			g.setColor(Color.RED);
			g.fillRect(0,  0,  sirina / 3,  visina / 3);
			g.setColor(Color.GREEN);
			g.drawRect(0,  0,  sirina / 3,  visina / 3);
			g.translate(- sirina + 1 + sirina / 3,  visina - 1 - visina / 3);
			g.setColor(Color.YELLOW);
			g.fillOval(0,  0,  sirina/ 3,  visina/ 3);
			g.setColor(Color.BLUE);
			g.drawOval(0,  0,  sirina / 3,  visina / 3);
		}
	}
	public test() {
		super("Crtanje");
		addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent we) {dispose();} //x na djalogu
		});
		add(new Platno());
		setSize(300, 300);
		setVisible(true);
	}
	public static void main(String[] args) {
		new test();
	}
}
*/
//----------------------------------------------------------------------------------------------
/*
public class test extends Frame implements ActionListener{
	TextField poljeZaTekst = new TextField("Uneti tekst ovde.");
	TextArea prostorZaTekst = new TextArea("I bice umetnut ovde");
	public test() {
		super("Tekst");
		dodajKomponente();
		setSize(200, 150);
		setVisible(true);
	}
	private void dodajKomponente() {
		add(poljeZaTekst, BorderLayout.NORTH);
		add(prostorZaTekst, BorderLayout.CENTER);
		poljeZaTekst.addActionListener(this);
	}
	@Override
	public void actionPerformed(ActionEvent e) {
		String tekst = poljeZaTekst.getText();
		if(tekst.equals("Kraj"))
			dispose();
		prostorZaTekst.insert(tekst + "\n", 0);		
	}
	public static void main(String[] args) {
		new test();
	}
	
}
*/
//----------------------------------------------------------------------------------------------
/*
public class test extends Frame implements ItemListener{
	Label labela = new Label("Pocetni tekst");
	Choice izbor = new Choice();
	List lista = new List(3, true);
	public test() {
		super("Liste");
		dodajKomponente();
		setSize(200, 200);
		setVisible(true);
	}
	private void dodajKomponente() {
		add(labela, BorderLayout.NORTH);
		labela.setAlignment(Label.CENTER);
		izbor.add("jedan");
		izbor.add("dva");
		izbor.add("Kraj");
		izbor.addItemListener(this);
		lista.add("tri");
		lista.add("cetiri");
		lista.add("pet");
		lista.addItemListener(this);
		Panel panel = new Panel(), panel1 = new Panel(), panel2 = new Panel();
		panel1.add(izbor);
		panel2.add(lista);
		panel.add(panel1);
		panel.add(panel2);
		add(panel, BorderLayout.CENTER);
	}
	@Override
	public void itemStateChanged(ItemEvent arg0) {
		String tekst = izbor.getSelectedItem() + " ";
		if(tekst.equals("Kraj "))
			dispose();
		for(int i = 0; i < lista.getItemCount(); ++i)
			if(lista.isIndexSelected(i))
				tekst += lista.getItem(i) + " ";
		labela.setText(tekst);
		
	}
	public static void main(String[] args) {
		new test();
	}
}
*/
//----------------------------------------------------------------------------------------------
/*
public class test extends Frame implements ItemListener{
	Label labela = new Label("Pocetni tekst");
	Checkbox poljeZaPotvrdu[] = new Checkbox[4];
	public test() {
		super("Polja za potvrdu");
		dodajKomponente();
		setSize(250, 120);
		setVisible(true);
	}

	void dodajKomponente() {
		add(labela, BorderLayout.NORTH);     //gde ce biti tekst
		labela.setAlignment(Label.CENTER);    //isto
		Panel panel = new Panel();
		Panel panel1 = new Panel();
		panel1.setLayout(new GridLayout(2,1));
		Panel panel2 = new Panel();
		panel2.setLayout(new GridLayout(2,1));
		poljeZaPotvrdu[0] = new Checkbox("jedan");
		poljeZaPotvrdu[1] = new Checkbox("dva");
		CheckboxGroup grupa = new CheckboxGroup();
		poljeZaPotvrdu[2] = new Checkbox("tri", grupa ,false);
		poljeZaPotvrdu[3] = new Checkbox("cetiri", grupa ,false);
		for(int i = 0; i < 4; ++i)
			poljeZaPotvrdu[i].addItemListener(this);
		for(int i = 0; i < 2; ++i)
			panel1.add(poljeZaPotvrdu[i]);    //u prvi panel dodaju se prva dva checkboxa
		for(int i = 2; i < 4; ++i)
			panel2.add(poljeZaPotvrdu[i]);    //u drugi druga dva
		panel.add(panel1);                    //u objedinjeni panel se dodaju dva panela
		panel.add(panel2);
		add(panel, BorderLayout.CENTER);
	}


	@Override
	public void itemStateChanged(ItemEvent e) {
		String tekst = "";
		for(int i = 0; i < 4; ++i) {
			if(poljeZaPotvrdu[i].getState())
				tekst += poljeZaPotvrdu[i].getLabel() + "";
		}
		labela.setText(tekst);
		if(tekst.equals("cetiri "))
			dispose();
		
	}
	
	public static void main(String[] args) {
		new test();
	}
}
*/
//----------------------------------------------------------------------------------------------
/*
public class test extends Frame implements ActionListener{
	Label labela = new Label("Pocetni tekst");
	public test() {
		super("Tasteri");
		dodajKomponente();
		setSize(250, 100);
		setVisible(true);
	}

	void dodajKomponente() {
		add(labela, BorderLayout.SOUTH);     //gde ce biti tekst
		labela.setAlignment(Label.RIGHT);    //isto
		Button jedan = new Button("jedan"),
				dva = new Button("dva"),
				tri = new Button("tri");
		tri.setActionCommand("Kraj");        //setuje se sta radi komanda
		jedan.addActionListener(this);
		dva.addActionListener(this);
		tri.addActionListener(this);
		Panel panel = new Panel();
		panel.add(jedan);
		panel.add(dva);
		panel.add(tri);
		add(panel, BorderLayout.CENTER);		
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		labela.setText(e.getActionCommand());
		if(labela.getText().equals("Kraj"))
			dispose();		
	}
	
	public static void main(String[] args) {
		new test();
	}
	
}
*/
//----------------------------------------------------------------------------------------------
/*
public class test extends Frame{
	public test() {
		super("Raspored");
		setSize(220, 270);
		dodajPanele();
		addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent we) {dispose();} //x na djalogu
		});
		setVisible(true);
		
	}

	private void dodajPanele() {
		setLayout(new GridLayout(2,2));
		Panel flow = new Panel();
		Panel card = new Panel();
		Panel border = new Panel();
		Panel grid = new Panel();
		card.setLayout(new CardLayout());
		border.setLayout(new BorderLayout());
		grid.setLayout(new GridLayout(2, 3));
		dodajTastere(flow);
		dodajTastere(card);
		dodajTastere(border);
		dodajTastere(grid);
		add(flow);
		add(card);
		add(border);
		add(grid);
	}
	
	private void dodajTastere(Panel panel) {
		panel.add(new Button("jedan"), BorderLayout.NORTH);
		panel.add(new Button("dva"), BorderLayout.WEST);
		panel.add(new Button("tri"), BorderLayout.SOUTH);
		panel.add(new Button("cetiri"), BorderLayout.EAST);
		panel.add(new Button("pet"), BorderLayout.CENTER);
	}

	public static void main(String[] args) {
		new test();
	}
}
*/
//------------------------------------------------------------------------------------------
/*
public class test extends Frame{
	public test() {
		super("Panel primer");
		setSize(150, 100);
		dodajPanele();
		addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent we) {dispose();} //x na djalogu
		});
		setVisible(true);
		
	}

	private void dodajPanele() {
		Panel panel1 = new Panel();
		panel1.setBackground(Color.green);
		panel1.add(new Button("jedan"));
		panel1.add(new Button("dva"));
		add(panel1, BorderLayout.WEST);
		Panel panel2 = new Panel();
		panel2.setBackground(Color.yellow);
		panel2.add(new Button("tri"));
		panel2.add(new Button("cetiri"));
		add(panel2, BorderLayout.SOUTH);	
	}
	public static void main(String[] args) {
		new test();
	}
}
*/
//-----------------------------------------------------------------------------------------
/*
public class test extends Frame implements ActionListener{
	class Dijalog extends Dialog{
		Dijalog(Frame roditelj){
			super(roditelj, "Dijalog", false);
			setSize(130, 80);
			addWindowListener(new WindowAdapter() {
				public void windowClosing(WindowEvent we) {setVisible(false);} //x na djalogu
			});
		}
	}
	private Dijalog dijalog;
	public test() {
		super("Primer Dijaloga");
		setSize(130, 80);
		addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent we) {dispose();} //x na djalogu
		});
		dodajMenije();
		dijalog = new Dijalog(this);
		setVisible(true);
	}
	
	private void dodajMenije() {
		MenuBar trakaMenija = new MenuBar();
		Menu meni = new Menu("Komande");
		meni.add("Otvori");
		meni.add("Zatvori");
		meni.add("Kraj");
		meni.addActionListener(this);
		trakaMenija.add(meni);
		setMenuBar(trakaMenija);
		
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		String komanda = e.getActionCommand();
		if(komanda.equals("Kraj")) dispose();
		else if(komanda.equals("Otvori")) dijalog.setVisible(true);
		else if(komanda.equals("Zatvori")) dijalog.setVisible(false);
		
	}
	public static void main(String[] args) {
		new test();
	}
}
*/
//------------------------------------------------------------------------------------------
/*
public class test extends Frame implements ActionListener{
	String izborIzMenija = "Izaberite stavku iz menija...";
	public test() {
		super("Meni");
		setSize(300, 200);
		dodajMenije();
		setVisible(true);
	}
	
	void dodajMenije() {
		MenuBar trakaMenija = new MenuBar();
		Menu prviMeni = new Menu("Prvi Meni");
		Menu drugiMeni = new Menu("Drugi Meni");
		prviMeni.add("Prvi meni, prva stavka");
		prviMeni.add("Prvi meni, druga stavka");
		prviMeni.add("Kraj");
		prviMeni.addActionListener(this);
		drugiMeni.add("Drugi meni, prva stavka");
		drugiMeni.add("Drugi meni, druga stavka");
		drugiMeni.addActionListener(this);
		trakaMenija.add(prviMeni);
		trakaMenija.add(drugiMeni);
		setMenuBar(trakaMenija);
	}
	public void paint(Graphics g) {
		g.drawString(izborIzMenija,  50,  100);
	}
	public void actionPerformed(ActionEvent e) {
		String komanda = e.getActionCommand();
		if(komanda.equals("Kraj")) dispose();
		else {
			izborIzMenija = "Izabrali ste " + komanda +".";
			repaint();
		}
	}
	public static void main(String[] args) {
		new test();
	}
}
*/
//-------------------------------------------------------------------------------------------
/*
public class test extends Frame implements MouseListener{
	
	class AdapterProzora extends WindowAdapter{
		public void windowClosing(WindowEvent we) {dispose();}
	}
	private String t = "ceka se dogadjaj misa";
	public test() {
		super("osluskivac misa");
		setSize(300, 100);
		addMouseListener(this);
		addWindowListener(new AdapterProzora());
		setVisible(true);
	}
	public void paint(Graphics g) {g.drawString(t,  50,  50);}
	public void mouseClicked(MouseEvent d) {t = "Dog: clicked"; repaint();}
	public void mouseEntered(MouseEvent d) {t = "Dog: entered"; repaint();}
	public void mouseExited(MouseEvent d) {t = "Dog: exited"; repaint();}
	public void mousePressed(MouseEvent d) {t = "Dog: pressed"; repaint();}
	public void mouseReleased(MouseEvent d) {t = "Dog: released"; repaint();}
	
	public static void main(String[] args) {
		new test();
	}
}
*/
//------------------------------------------------------------------------------------------
/*
public class test extends Frame{
	class AdapterProzora extends WindowAdapter{
		public void windowClosing(WindowEvent we) {dispose();}
	}
	public test() {
		super("Primer adaptera");
		setSize(280, 80);
		addWindowListener(new AdapterProzora());
		
		//ili addWindowListener(new WindowAdapter(){
		 	public void windowClosing(WindowEvent we) {dispose();}
		 }
		 
		setVisible(true);
	}
	public void paint(Graphics g) {
		g.drawString("Zdravo", 50, 50);
	}
	public static void main(String[] args) {
		new test();
	}
}
*/
//------------------------------------------------------------------------------------------
/*
	class test extends Frame implements ActionListener {
	    private Button dugme;
	    private int broj = 0;
	    
	    public test(){
	        super("Brojanje");
	        setSize(200,200);
	        kreirajDugme();
	        setVisible(true);
	    }
	    private void kreirajDugme(){
	        dugme = new Button("Pritisni");
	        add(dugme);
	        dugme.addActionListener(this);
	    }
	    public void actionPerformed(ActionEvent e){
	        dugme.setLabel("Pritisnuto" + ++ broj + ".put");
	    }
	    
	    public static void main(String[] args){
	        new test(); 
	    }

}
*/