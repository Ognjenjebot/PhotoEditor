package operations;

import java.util.ArrayList;

import gui.Layer;
import gui.Selection;

public class GreyShadesOperation extends Operation {

	@Override
	public void execute(Layer i, int num) {
		Selection s = i.parent.getSelection();
		ArrayList<Integer> indexes = s.pixelSelection(i.width, i.height);
		
		
		if (indexes.size() == 0) {//cela slika
			for (int j=0; j<i.pixels.size(); j++) {
				int a = ((i.pixels.get(j).B + i.pixels.get(j).G + i.pixels.get(j).R) / 3);
				i.pixels.get(j).A = (byte) a;
				i.pixels.get(j).R = (byte) a;
				i.pixels.get(j).G = (byte) a;
				i.pixels.get(j).B = (byte) a;
			}
		} else { //selekcija
			for (int j=0; j<indexes.size(); j++) {
				int index = indexes.get(j).intValue();
				int a = ((i.pixels.get(index).B + i.pixels.get(index).G + i.pixels.get(index).R) / 3);
				i.pixels.get(index).A = (byte) a; //PAZI DA NE PRODJE [0,255]
				i.pixels.get(index).R = (byte) a;
				i.pixels.get(index).G = (byte) a;
				i.pixels.get(index).B = (byte) a;
			}
		}
	}
}
