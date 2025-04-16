/*
 * Aman Hogan-Bailey 1001830469
 */
package code6_1001830469;

import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Random;
import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JTextField;
import javax.swing.SwingConstants;

/**
 *
 * @author Aman
 */
public class GameFrame extends JFrame
{
    //Declare Final Variables
    private final JLabel label1;
    private final JButton OKButton;
    private final JButton CancelButton;
    private final JTextField textField1;
    
    //Holds Characters' Names
    public String CCName = "";
    
    public GameFrame()
    {
        super();
        setLayout(new FlowLayout());
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        //Randome Number between 1 and 4
        Random r = new Random();
        int randomNumber = r.nextInt(4)+1;
        switch(randomNumber)
        {
            case 1 :
                CCName = "George";
                break;
            case 2 :
                CCName = "Jerry";
                break;
            case 3 :
                CCName = "Kramer";
                break;
            case 4 :
                CCName = "Elaine";
                break;
            default :
        }
        
        //Icon equals the image in class//
        Icon CC = new ImageIcon(getClass().getResource(CCName + ".png"));
        
        //New Jlabel
        label1 = new JLabel();
        label1.setText("Who is this TV Show character?");
        label1.setIcon(CC);
        label1.setHorizontalTextPosition(SwingConstants.CENTER);
        label1.setVerticalTextPosition(SwingConstants.BOTTOM);
        label1.setToolTipText("The person is a comedian...");
        add(label1);
        
        EventHandler handler = new EventHandler();
        
        textField1 = new JTextField("Type your answer here");
        textField1.selectAll();
        textField1.addActionListener(handler);
        add(textField1);
        
        OKButton = new JButton("OK");
        OKButton.addActionListener(handler);
        add(OKButton);
    
        CancelButton = new JButton("Cancel");
        CancelButton.addActionListener(handler);
        add(CancelButton);   
    }
    
    private class EventHandler implements ActionListener
    {
        
        public void actionPerformed(ActionEvent event)
        {
            String enteredString = "";
            String response = "";
            boolean guess = false;
            
            enteredString = textField1.getText();
            
            if (enteredString.equalsIgnoreCase(CCName))
            {
                response = "You guessed Correctly";
                guess = true;
            }
            else
            {
                response = "That is not Correct...";
            }
            
            if(event.getSource() == OKButton || event.getSource() == textField1 )
            {
                JOptionPane.showMessageDialog(null, response);
                
                if(guess == true)
                {
                    System.exit(0);
                }
            }
            
            else if(event.getSource()  == CancelButton)
            {
                System.exit(0);
            }
                
        }
    }
                 
}
