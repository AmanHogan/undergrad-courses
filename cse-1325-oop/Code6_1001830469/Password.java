/*
 * Aman Hogan-Bailey 1001830469
 */
package code6_1001830469;

import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.beans.EventHandler;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPasswordField;
import javax.swing.JTextField;

/**
 *
 * @author Aman
 */
public class Password extends JFrame
{
    private final JPasswordField passwordField;
    public String enteredPassword = "";
    public final String actualPassword = "5119";

    public Password()
    {
        super("Enter the Password to Continue");
        setLayout(new FlowLayout());
        
        passwordField = new JPasswordField(10);
        passwordField.setEchoChar('X');
        add(passwordField);
        
        EventHandler handler = new EventHandler();
        passwordField.addActionListener(handler);

    }

    private class EventHandler implements ActionListener
    {
        public void actionPerformed(ActionEvent event)
        {
            if (event.getSource() == passwordField)
            {
                enteredPassword = event.getActionCommand();
            }
       
            if(enteredPassword.equalsIgnoreCase(actualPassword))
            {
                passwordField.setVisible(false);
                GameFrame gameframe = new GameFrame();
                gameframe.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
                gameframe.setSize(1200,1200);
                gameframe.setVisible(true);
            }
            
            if(!(enteredPassword.equalsIgnoreCase(actualPassword)))
            {
                JOptionPane.showMessageDialog(null, "Invalid Password...please try again");
            }
        }
    }
}