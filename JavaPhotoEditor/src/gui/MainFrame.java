package gui;

import java.awt.BorderLayout;
import java.awt.Frame;
import java.awt.Menu;
import java.awt.MenuBar;
import java.awt.MenuItem;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.ArrayList;
import java.util.List;

import javax.swing.JFileChooser;
import javax.swing.JOptionPane;

import operations.BasicOperation1;
import operations.BasicOperation10;
import operations.BasicOperation11;
import operations.BasicOperation2;
import operations.BasicOperation3;
import operations.BasicOperation4;
import operations.BasicOperation5;
import operations.BasicOperation6;
import operations.BasicOperation7;
import operations.BasicOperation8;
import operations.BasicOperation9;
import operations.BlackWhiteOperation;
import operations.GreyShadesOperation;
import operations.InverseOperation;
import operations.MedianaOperation;
import operations.Operation;

public class MainFrame extends Frame {
	private Image image;
	private MainCanvas mainCanvas;
	private final JFileChooser fc = new JFileChooser();
	private boolean selectionInProgress = false;
	private boolean composite = false;

	private MouseAdapter selectionListener = new MouseAdapter() {
		private int numberOfClicks = 0;
		private int x1, y1, x2, y2;
		@Override
		public void mouseClicked(MouseEvent event) {
			if (!selectionInProgress) return;
			
			numberOfClicks++;
			if (numberOfClicks == 1) {
				x1 = event.getX();
				y1 = event.getY();
				//napisi u naslovu koordinate
				MainFrame.this.setTitle("gornja tacka = (" + x1 + "," + y1 + ")");
			} else { 				
				x2 = event.getX();
				y2 = event.getY();
				
				//za crtanje rectangla moraju da se salju koordinate gornjeg levog ugla
				Rectangle r = new Rectangle(x1, y1, x2-x1, y2-y1);
				MainFrame.this.mainCanvas.addRectangle(r);
				JOptionPane.showMessageDialog(MainFrame.this, "selekcija dodata \n(" + x1 + "," + y1 +")(" + x2 + "," + y2 + ")");
				
				MainFrame.this.setTitle("Obrada slika");
				
				MainFrame.this.mainCanvas.repaint();	//da bi se nacrtao rectangle, ne sluzi za efekat			
				
				numberOfClicks = 0;
				selectionInProgress = false;
			}
			
		}
		
	};
	
	
	public MainFrame() {
		setTitle("Obrada slika");
		setSize(1024, 1024);
		
		mainCanvas = new MainCanvas();
		mainCanvas.addMouseListener(selectionListener);
		add(mainCanvas, BorderLayout.CENTER);

		addWindowListener(new WindowAdapter() {
			@Override
			public void windowClosing(WindowEvent e) {
				dispose();
			}
		});
		
		image = new Image();
		//image.drawBMPImage("D:\\FAKULTET OBAVEZE\\materijal za poop projekat\\smp2.bmp", mainCanvas);  
		
		setResizable(true);
		setMenuBar(new Traka());
		setVisible(true);
		

	}
	
	private class Traka extends MenuBar{
		public Traka() {
			Menu meni = new Menu("Fajl");    
			add(meni);
			MenuItem stavka1 = new MenuItem("Ubaci sliku");
			meni.add(stavka1);
			stavka1.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					// fajl sistem		
					fc.showOpenDialog(null);
					String path = fc.getSelectedFile().getAbsolutePath();
					image.drawBMPImage(path,  mainCanvas);
				}	
			});
			MenuItem stavka2 = new MenuItem("Exportuj sliku");
			meni.add(stavka2);
			stavka2.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					fc.showOpenDialog(null);
					String path = fc.getSelectedFile().getAbsolutePath();
					image.exportImage(path);				
				}			
			});
			MenuItem stavka110 = new MenuItem("Spoji slike");
			meni.add(stavka110);
			stavka110.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					image.mergeLayers();
					MainFrame.this.mainCanvas.repaint();
				}			
			});
			MenuItem stavka111 = new MenuItem("Transparentnost slojeva");
			meni.add(stavka111);
			stavka111.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					String result = (String)JOptionPane.showInputDialog(
					           MainFrame.this,
					           "Parameter", 
					           "Transparency",            
					           JOptionPane.PLAIN_MESSAGE,
					           null,            
					           null, 
					           "50"
					        );
					int t = Integer.parseInt(result);
					image.addTransparency(t);
					MainFrame.this.mainCanvas.repaint();
				}			
			});
			meni.add(stavka1 = new MenuItem("Izlaz"));
			stavka1.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					dispose();				
				}				
			});
			
			Menu selections = new Menu("Selekcije");
			add(selections);
			MenuItem nova = new MenuItem("Nova selekcija");
			selections.add(nova);
			nova.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					selectionInProgress = true;
					JOptionPane.showMessageDialog(MainFrame.this, "Selection mode activated.\n"
							+ "Click on first upper left point, \n"
							+ "then click on down right point.\n"
							+ "Successfull selection message should appear\n"
							+ "afterwards.");
				}				
			});
			
			Menu operations = new Menu("Operacije");
			add(operations);
			MenuItem basic1 = new MenuItem("ADD");
			operations.add(basic1);
			basic1.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					String result = (String)JOptionPane.showInputDialog(
					           MainFrame.this,
					           "Operation parameter", 
					           "ADD",            
					           JOptionPane.PLAIN_MESSAGE,
					           null,            
					           null, 
					           "50"
					        );
					try {
						int num = Integer.parseInt(result);
						new BasicOperation1().execute(mainCanvas.layer, num);
						if(!composite)
							MainFrame.this.mainCanvas.repaint();
					} catch (NumberFormatException ex) {}
				}				
			});
			MenuItem basic2 = new MenuItem("SUBTRACT");
			operations.add(basic2);
			basic2.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					String result = (String)JOptionPane.showInputDialog(
					           MainFrame.this,
					           "Operation parameter", 
					           "SUBTRACT",            
					           JOptionPane.PLAIN_MESSAGE,
					           null,            
					           null, 
					           "50"
					        );
					try {
						int num = Integer.parseInt(result);
						new BasicOperation2().execute(mainCanvas.layer, num);
						if(!composite)
							MainFrame.this.mainCanvas.repaint();
					} catch (NumberFormatException ex) {}
				}				
			});
			MenuItem basic3 = new MenuItem("SUBTRACT type2");
			operations.add(basic3);
			basic3.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					String result = (String)JOptionPane.showInputDialog(
					           MainFrame.this,
					           "Operation parameter", 
					           "SUBTRACT type2",            
					           JOptionPane.PLAIN_MESSAGE,
					           null,            
					           null, 
					           "150"
					        );
					try {
						int num = Integer.parseInt(result);
						new BasicOperation3().execute(mainCanvas.layer, num);
						if(!composite)
							MainFrame.this.mainCanvas.repaint();
					} catch (NumberFormatException ex) {}
				}				
			});
			MenuItem basic4 = new MenuItem("MULTIPLY");
			operations.add(basic4);
			basic4.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					String result = (String)JOptionPane.showInputDialog(
					           MainFrame.this,
					           "Operation parameter", 
					           "MULTIPLY",            
					           JOptionPane.PLAIN_MESSAGE,
					           null,            
					           null, 
					           "2"
					        );
					try {
						int num = Integer.parseInt(result);
						new BasicOperation4().execute(mainCanvas.layer, num);
						if(!composite)
							MainFrame.this.mainCanvas.repaint();
					} catch (NumberFormatException ex) {}
				}				
			});
			MenuItem basic5 = new MenuItem("DIVIDE");
			operations.add(basic5);
			basic5.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					String result = (String)JOptionPane.showInputDialog(
					           MainFrame.this,
					           "Operation parameter", 
					           "DIVIDE",            
					           JOptionPane.PLAIN_MESSAGE,
					           null,            
					           null, 
					           "2"
					        );
					try {
						int num = Integer.parseInt(result);
						new BasicOperation5().execute(mainCanvas.layer, num);
						if(!composite)
							MainFrame.this.mainCanvas.repaint();
					} catch (NumberFormatException ex) {}
				}				
			});
			MenuItem basic6 = new MenuItem("DIVIDE type2");
			operations.add(basic6);
			basic6.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					String result = (String)JOptionPane.showInputDialog(
					           MainFrame.this,
					           "Operation parameter", 
					           "DIVIDE type2",            
					           JOptionPane.PLAIN_MESSAGE,
					           null,            
					           null, 
					           "2"
					        );
					try {
						int num = Integer.parseInt(result);
						new BasicOperation6().execute(mainCanvas.layer, num);
						if(!composite)
							MainFrame.this.mainCanvas.repaint();
					} catch (NumberFormatException ex) {}
				}				
			});
			MenuItem basic7 = new MenuItem("POWER");
			operations.add(basic7);
			basic7.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					String result = (String)JOptionPane.showInputDialog(
					           MainFrame.this,
					           "Operation parameter", 
					           "POWER",            
					           JOptionPane.PLAIN_MESSAGE,
					           null,            
					           null, 
					           "2"
					        );
					try {
						int num = Integer.parseInt(result);
						new BasicOperation7().execute(mainCanvas.layer, num);
						if(!composite)
							MainFrame.this.mainCanvas.repaint();
					} catch (NumberFormatException ex) {}
				}				
			});
			MenuItem basic8 = new MenuItem("LOG");
			operations.add(basic8);
			basic8.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {					
									
						new BasicOperation8().execute(mainCanvas.layer, 0);
						if(!composite)
							MainFrame.this.mainCanvas.repaint();
					
				}				
			});
			MenuItem basic9 = new MenuItem("ABS");
			operations.add(basic9);
			basic9.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					
						new BasicOperation9().execute(mainCanvas.layer, 0);
						if(!composite)
							MainFrame.this.mainCanvas.repaint();
				}				
			});
			MenuItem basic10 = new MenuItem("MIN");
			operations.add(basic10);
			basic10.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					String result = (String)JOptionPane.showInputDialog(
					           MainFrame.this,
					           "Operation parameter", 
					           "MIN",            
					           JOptionPane.PLAIN_MESSAGE,
					           null,            
					           null, 
					           ""
					        );
					try {
						int num = Integer.parseInt(result);
						new BasicOperation10().execute(mainCanvas.layer, num);
						if(!composite)
							MainFrame.this.mainCanvas.repaint();
					} catch (NumberFormatException ex) {}
				}				
			});
			MenuItem basic11 = new MenuItem("MAX");
			operations.add(basic11);
			basic11.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					String result = (String)JOptionPane.showInputDialog(
					           MainFrame.this,
					           "Operation parameter", 
					           "MAX",            
					           JOptionPane.PLAIN_MESSAGE,
					           null,            
					           null, 
					           ""
					        );
					try {
						int num = Integer.parseInt(result);
						new BasicOperation11().execute(mainCanvas.layer, num);
						if(!composite)
							MainFrame.this.mainCanvas.repaint();
					} catch (NumberFormatException ex) {}
				}				
			});
			MenuItem greyshades = new MenuItem("GreyShadesOperation");
			operations.add(greyshades);
			greyshades.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
				
						new GreyShadesOperation().execute(mainCanvas.layer, 0);
						MainFrame.this.mainCanvas.repaint();
				}				
			});
			MenuItem mediana = new MenuItem("MedianaOperation");
			operations.add(mediana);
			mediana.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					
						new MedianaOperation().execute(mainCanvas.layer, 0);
						if(!composite)
							MainFrame.this.mainCanvas.repaint();
				}				
			});
			MenuItem inverse = new MenuItem("InverseOperation");
			operations.add(inverse);
			inverse.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					
						new InverseOperation().execute(mainCanvas.layer, 0);
						if(!composite)
							MainFrame.this.mainCanvas.repaint();
				}				
			});
			MenuItem blackwhite = new MenuItem("BlackWhiteOperation");
			operations.add(blackwhite);
			blackwhite.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {

						new BlackWhiteOperation().execute(mainCanvas.layer, 0);
						if(!composite)
							MainFrame.this.mainCanvas.repaint();
				}				
			});
			MenuItem multy = new MenuItem("CompositeOperation");
			operations.add(multy);
			multy.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
						composite = true;												
						MainFrame.this.mainCanvas.repaint();
				}				
			});
			MenuItem ex = new MenuItem("ExecuteCompositeOperation");
			operations.add(ex);
			ex.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
						composite = false;
						MainFrame.this.mainCanvas.repaint();
				}				
			});
			
			Menu meni3 = new Menu("Popuni bojom");    
			add(meni3);
			MenuItem stavka100 = new MenuItem("Plava");
			meni3.add(stavka100);
			stavka100.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					mainCanvas.selection.fillBlue(mainCanvas.layer);
					MainFrame.this.mainCanvas.repaint();
				}	
			});
			MenuItem stavka101 = new MenuItem("Crvena");
			meni3.add(stavka101);
			stavka101.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					mainCanvas.selection.fillRed(mainCanvas.layer);
					MainFrame.this.mainCanvas.repaint();
				}	
			});
			MenuItem stavka102 = new MenuItem("Zelena");
			meni3.add(stavka102);
			stavka102.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					mainCanvas.selection.fillGreen(mainCanvas.layer);
					MainFrame.this.mainCanvas.repaint();
				}	
			});
		}
	}

	public static void main(String [] args) {
		new MainFrame();
	}
}
