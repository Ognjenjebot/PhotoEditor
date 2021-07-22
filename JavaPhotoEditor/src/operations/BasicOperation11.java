package operations;

import java.util.ArrayList;

import gui.Layer;
import gui.Selection;

public class BasicOperation11 extends Operation {

	@Override
	public void execute(Layer i, int num) {
		Selection s = i.parent.getSelection();
		ArrayList<Integer> indexes = s.pixelSelection(i.width, i.height);
		
		
		if (indexes.size() == 0) {//cela slika
			for (int j=0; j<i.pixels.size(); j++) {
				if(i.pixels.get(j).A < num)
				i.pixels.get(j).A = (byte) num;
				if(i.pixels.get(j).R < num)
				i.pixels.get(j).R = (byte) num;
				if(i.pixels.get(j).G < num)
				i.pixels.get(j).G = (byte) num;
				if(i.pixels.get(j).B < num)
				i.pixels.get(j).B = (byte) num;
			}
		} else { //selekcija
			for (int j=0; j<indexes.size(); j++) {
				int index = indexes.get(j).intValue();
				if(i.pixels.get(index).A < num)
					i.pixels.get(index).A = (byte) num;
				if(i.pixels.get(index).R < num)
					i.pixels.get(index).R = (byte) num;
				if(i.pixels.get(index).G < num)
					i.pixels.get(index).G = (byte) num;
				if(i.pixels.get(index).B < num)
					i.pixels.get(index).B = (byte) num;
			}
		}
	}
}
