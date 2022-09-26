/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import javax.swing.*;
import java.sql.*;
import java.sql.Statement;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author 1061
 */
public class demo1 extends javax.swing.JFrame {

    /**
     * Creates new form demo1
     */
    Connection con;
    Statement st;
    PreparedStatement ps;
    ResultSet rs;
   
    public demo1() {
        initComponents();
        try{
            Class.forName("oracle.jdbc.OracleDriver");
            JOptionPane.showMessageDialog(this,"Driver Loaded!");
        try {
            con = DriverManager.getConnection("jdbc:oracle:thin:@10.6.4.33:1521:orcl","1061","1061");
            JOptionPane.showMessageDialog(this,"Connected to Oracle database!");
        }
        catch (SQLException ex) {
            Logger.getLogger(demo1.class.getName()).log(Level.SEVERE, null, ex);
            JOptionPane.showMessageDialog(this,ex.getMessage());
        }
        }
        catch(ClassNotFoundException ex){
        Logger.getLogger(demo1.class.getName()).log(Level.SEVERE, null, ex);
        JOptionPane.showMessageDialog(this,ex.getMessage());
        }

    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">                          
    private void initComponents() {

        SEX1 = new javax.swing.JLabel();
        EID = new javax.swing.JLabel();
        NAME = new javax.swing.JLabel();
        DOB = new javax.swing.JLabel();
        SEX = new javax.swing.JLabel();
        DESIGNATION = new javax.swing.JLabel();
        BASICPAY = new javax.swing.JLabel();
        name = new javax.swing.JTextField();
        eid = new javax.swing.JTextField();
        sex = new javax.swing.JTextField();
        dob = new javax.swing.JTextField();
        bp = new javax.swing.JTextField();
        designation = new javax.swing.JTextField();
        insert = new javax.swing.JButton();
        update = new javax.swing.JButton();
        delete = new javax.swing.JButton();
        refresh = new javax.swing.JButton();
        search = new javax.swing.JButton();
        jLabel1 = new javax.swing.JLabel();
        exit = new javax.swing.JButton();

        SEX1.setText("SEX");

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);

        EID.setText("EID");

        NAME.setText("NAME");

        DOB.setText("DATE OF BIRTH");

        SEX.setText("SEX");

        DESIGNATION.setText("DESIGNATION");

        BASICPAY.setText("BASIC PAY");

        eid.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                eidActionPerformed(evt);
            }
        });

        sex.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                sexActionPerformed(evt);
            }
        });

        insert.setText("INSERT");
        insert.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                insertActionPerformed(evt);
            }
        });

        update.setText("UPDATE");
        update.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                updateActionPerformed(evt);
            }
        });

        delete.setText("DELETE");
        delete.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                deleteActionPerformed(evt);
            }
        });

        refresh.setText("REFRESH");
        refresh.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                refreshActionPerformed(evt);
            }
        });

        search.setText("SEARCH");
        search.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                searchActionPerformed(evt);
            }
        });

        jLabel1.setText("EMPLOYEE  DATABASE");

        exit.setText("EXIT");
        exit.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                exitActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGap(61, 61, 61)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                        .addGroup(layout.createSequentialGroup()
                            .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                                .addComponent(BASICPAY, javax.swing.GroupLayout.PREFERRED_SIZE, 93, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addComponent(DESIGNATION, javax.swing.GroupLayout.PREFERRED_SIZE, 93, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addComponent(SEX, javax.swing.GroupLayout.PREFERRED_SIZE, 93, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addComponent(DOB, javax.swing.GroupLayout.PREFERRED_SIZE, 93, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addComponent(NAME, javax.swing.GroupLayout.PREFERRED_SIZE, 93, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addComponent(EID, javax.swing.GroupLayout.PREFERRED_SIZE, 93, javax.swing.GroupLayout.PREFERRED_SIZE))
                            .addGap(65, 65, 65)
                            .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                .addComponent(eid)
                                .addComponent(bp)
                                .addComponent(designation)
                                .addComponent(name)
                                .addComponent(dob)
                                .addComponent(sex)))
                        .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                            .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                                .addComponent(insert, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                .addComponent(search))
                            .addGap(18, 18, 18)
                            .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                .addComponent(update, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                .addComponent(refresh, javax.swing.GroupLayout.DEFAULT_SIZE, 90, Short.MAX_VALUE))
                            .addGap(20, 20, 20)
                            .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                                .addComponent(delete, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                .addComponent(exit, javax.swing.GroupLayout.PREFERRED_SIZE, 69, javax.swing.GroupLayout.PREFERRED_SIZE))))
                    .addGroup(layout.createSequentialGroup()
                        .addGap(81, 81, 81)
                        .addComponent(jLabel1)))
                .addGap(57, 57, 57))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGap(23, 23, 23)
                .addComponent(jLabel1)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addGap(19, 19, 19)
                        .addComponent(EID))
                    .addGroup(layout.createSequentialGroup()
                        .addGap(18, 18, 18)
                        .addComponent(eid, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)))
                .addGap(1, 1, 1)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addGap(12, 12, 12)
                        .addComponent(NAME))
                    .addGroup(layout.createSequentialGroup()
                        .addGap(9, 9, 9)
                        .addComponent(name, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                    .addComponent(dob)
                    .addComponent(DOB, javax.swing.GroupLayout.PREFERRED_SIZE, 20, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(SEX)
                    .addComponent(sex, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(DESIGNATION)
                    .addComponent(designation))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(BASICPAY)
                    .addComponent(bp, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(18, 18, 18)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(insert)
                    .addComponent(update)
                    .addComponent(delete))
                .addGap(18, 18, 18)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(refresh)
                    .addComponent(search)
                    .addComponent(exit))
                .addGap(19, 19, 19))
        );

        pack();
    }// </editor-fold>                        

    private void eidActionPerformed(java.awt.event.ActionEvent evt) {                                    
        // TODO add your handling code here:
    }                                  

    private void refresh(){
        eid.setText("");
        name.setText("");
        designation.setText("");
        bp.setText("");
        dob.setText("");
        sex.setText("");
    }
    private void refreshActionPerformed(java.awt.event.ActionEvent evt) {                                        
        // TODO add your handling code here:
       
            refresh();
       
    }                                      

    private void sexActionPerformed(java.awt.event.ActionEvent evt) {                                    
        // TODO add your handling code here:
    }                                  
   
    private void insertActionPerformed(java.awt.event.ActionEvent evt) {                                      
        // TODO add your handling code here:
        try {
            String sql = "insert into emp_payroll values(?,?,?,?,?,?,NULL,NULL,NULL,NULL,NULL,NULL,NULL)";
            ps = con.prepareStatement(sql);
            ps.setString(1, eid.getText());
            ps.setString(2, name.getText());
            ps.setString(3, dob.getText());
            ps.setString(4, sex.getText());
            ps.setString(5, designation.getText());
            ps.setString(6, bp.getText());
            ps.execute();
            JOptionPane.showMessageDialog(this,"Inserted!");
            refresh();
            }
        catch (SQLException ex) {
            Logger.getLogger(demo1.class.getName()).log(Level.SEVERE, null, ex);
            JOptionPane.showMessageDialog(this,ex.getMessage());
        }
    }                                      

    private void deleteActionPerformed(java.awt.event.ActionEvent evt) {                                      
        // TODO add your handling code here:
        try{
            String sql = "delete from emp_payroll where eid=?";
            ps = con.prepareStatement(sql);
            ps.setString(1, eid.getText());
            ps.execute();
            JOptionPane.showMessageDialog(this, "Deleted!");
            refresh();
            }
            catch (SQLException ex) {
            Logger.getLogger(demo1.class.getName()).log(Level.SEVERE, null, ex);
            JOptionPane.showMessageDialog(this,ex.getMessage());
            }
    }                                      

    private void exitActionPerformed(java.awt.event.ActionEvent evt) {                                    
        // TODO add your handling code here:
        System.exit(0);
    }                                    

    private void searchActionPerformed(java.awt.event.ActionEvent evt) {                                      
        // TODO add your handling code here:
        try {
            String sql = "select * from emp_payroll where eid = '"+eid.getText()+"'";
            st = con.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE,ResultSet.CONCUR_UPDATABLE);
            rs = st.executeQuery(sql);
            if(rs.next()){
                eid.setText(rs.getString(1));
                name.setText(rs.getString(2));
                dob.setText(rs.getString(3));
                sex.setText(rs.getString(4));
                designation.setText(rs.getString(5));
                bp.setText(rs.getString(6));
                //String s=rs.getString(13);
                JOptionPane.showMessageDialog(this, "Record Found!");
            }
            else
                JOptionPane.showMessageDialog(this, "Record Not Found!");
            }
            catch (SQLException ex) {
                Logger.getLogger(demo1.class.getName()).log(Level.SEVERE, null, ex);
                JOptionPane.showMessageDialog(this, ex.getMessage());
            }
    }                                      

    private void updateActionPerformed(java.awt.event.ActionEvent evt) {                                      
        // TODO add your handling code here:
        try{
            String sql = "update emp_payroll set name=?,dob=?,sex=?,designation=?,bp=? where eid=?";
            ps = con.prepareStatement(sql);
            ps.setString(6, eid.getText());
            ps.setString(1, name.getText());
            ps.setString(2, dob.getText());
            ps.setString(3, sex.getText());
            ps.setString(4, designation.getText());
            ps.setString(5, bp.getText());
            ps.execute();
            JOptionPane.showMessageDialog(this, "Updated!");
            refresh();
            }
        catch (SQLException ex) {
            Logger.getLogger(demo1.class.getName()).log(Level.SEVERE, null, ex);
            JOptionPane.showMessageDialog(this,ex.getMessage());
        }
    }                                      

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        /* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html
         */
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(demo1.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(demo1.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(demo1.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(demo1.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new demo1().setVisible(true);
            }
        });
    }

    // Variables declaration - do not modify                    
    private javax.swing.JLabel BASICPAY;
    private javax.swing.JLabel DESIGNATION;
    private javax.swing.JLabel DOB;
    private javax.swing.JLabel EID;
    private javax.swing.JLabel NAME;
    private javax.swing.JLabel SEX;
    private javax.swing.JLabel SEX1;
    private javax.swing.JTextField bp;
    private javax.swing.JButton delete;
    private javax.swing.JTextField designation;
    private javax.swing.JTextField dob;
    private javax.swing.JTextField eid;
    private javax.swing.JButton exit;
    private javax.swing.JButton insert;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JTextField name;
    private javax.swing.JButton refresh;
    private javax.swing.JButton search;
    private javax.swing.JTextField sex;
    private javax.swing.JButton update;
    // End of variables declaration                  
}