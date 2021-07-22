package gui;

import java.awt.Canvas;
import java.awt.Color;
import java.awt.Graphics;
import java.util.ArrayList;

import gui.*;

public class Selection {
	private ArrayList<Rectangle> rectangles; 
	public boolean active;
	
	public Selection(ArrayList<Rectangle> rects) {
		rectangles = rects;
		active = true;
	}
	
	public Selection() {
		rectangles = new ArrayList<Rectangle>();
		active = true;
	}
	
	public Selection addRectangle(Rectangle r) {
		rectangles.add(r);
		return this;
	}
	
	public Selection drawSelection(Canvas canvas) {   //crta crveni pravougaonik, od gornjeg levog ugla
		Graphics g = canvas.getGraphics();
		if (g != null) {
			g.setColor(Color.RED);
			for (Rectangle r:rectangles) {
				g.drawRect(r.getX(), r.getY(), r.getWidth(), r.getHeight());
				System.out.println("visina i sirina " + r.getHeight() + "  "  + r.getWidth());
				System.out.println("X i Y " + r.getX() + "  "  + r.getY());
			}
		}
		return this;
	}
	
	//kao u c++ sto sam imao, vraca array pixela koji trebaju da se menjaju
	public ArrayList<Integer> pixelSelection(int layer_Width, int layer_Height) {
		ArrayList<Integer> temp = new ArrayList<Integer>();
		int m, n, x, y;
		for (Rectangle r : rectangles) {
			m = r.getHeight();   
			n = r.getWidth();   
			x = r.getX();  
			y = layer_Height - r.getY();   //mora da se oduzme od visine slike, jer sam u c++ imao koo.pocetak u donjem levom uglu, a uavi mi je u gornjem
			for (int i = 0; i < m; i++)	{
				for (int j = 0; j < n; j++)	{
					temp.add(Number(i, j, layer_Width, layer_Height, x, y));
				}
			}
		}
		return temp;
	}
	
	//koristi se samo uz pixelselection
	static Integer Number(int i, int j, int layer_Width, int layer_Height, int x, int y) {
		int new_y, new_x;
		new_y = y - i;
		new_x = x + j;
		return new Integer((new_y - 1)*layer_Width - 1 + new_x);
	}
	
	public void fillBlue(Layer i) {
		ArrayList<Integer> indexes = this.pixelSelection(i.width, i.height);
		
		if (indexes.size() == 0) {//cela slika
			for (int j=0; j<i.pixels.size(); j++) {
				i.pixels.get(j).A = (byte) 255;
				i.pixels.get(j).R = 0;
				i.pixels.get(j).G = 0;
				i.pixels.get(j).B = (byte) 255;
			}
		} else { //selekcija
			for (int j=0; j<indexes.size(); j++) {
				int index = indexes.get(j).intValue();
				i.pixels.get(index).A = (byte) 255;
				i.pixels.get(index).R = 0;
				i.pixels.get(index).G = 0;
				i.pixels.get(index).B = (byte) 255;
			}
		}
	}
	public void fillGreen(Layer i) {
		ArrayList<Integer> indexes = this.pixelSelection(i.width, i.height);
		
		if (indexes.size() == 0) {//cela slika
			for (int j=0; j<i.pixels.size(); j++) {
				i.pixels.get(j).A = (byte) 255;
				i.pixels.get(j).R = 0;
				i.pixels.get(j).G = (byte) 255;
				i.pixels.get(j).B = 0;
			}
		} else { //selekcija
			for (int j=0; j<indexes.size(); j++) {
				int index = indexes.get(j).intValue();
				i.pixels.get(index).A = (byte) 255;
				i.pixels.get(index).R = 0;
				i.pixels.get(index).G = (byte) 255;
				i.pixels.get(index).B = 0;
			}
		}
	}
	public void fillRed(Layer i) {
		ArrayList<Integer> indexes = this.pixelSelection(i.width, i.height);
		
		if (indexes.size() == 0) {//cela slika
			for (int j=0; j<i.pixels.size(); j++) {
				i.pixels.get(j).A = (byte) 255;
				i.pixels.get(j).R = (byte) 255;
				i.pixels.get(j).G = 0;
				i.pixels.get(j).B = 0;
			}
		} else { //selekcija
			for (int j=0; j<indexes.size(); j++) {
				int index = indexes.get(j).intValue();
				i.pixels.get(index).A = (byte) 255;
				i.pixels.get(index).R = (byte) 255;
				i.pixels.get(index).G = 0;
				i.pixels.get(index).B = 0;
			}
		}
	}
}