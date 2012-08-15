/*
 * Copyright Notice. Copyright 2011 Northwestern University and Stanford
 * University (“caBIG® Participant”). AIM Template Enterprise Service conforms
 * to caBIG® technical specifications and is part of the caBIG® initiative. The
 * software subject to this notice and license includes human readable source
 * code form, machine readable, binary, object code form and related
 * documentation (the “caBIG® Software”).
 *
 * This caBIG® Software License (the “License”) is between the National Cancer
 * Institute (NCI) and You. “You (or “Your”) shall mean a person or an entity,
 * and all other entities that control, are controlled by, or are under common
 * control with the entity. “Control” for purposes of this definition means (i)
 * the direct or indirect power to cause the direction or management of such
 * entity, whether by contract or otherwise, or (ii) ownership of fifty percent
 * (50%) or more of the outstanding shares, or (iii) beneficial ownership of
 * such entity.
 *
 * Provided that You agree to the conditions described below, NCI grants You a
 * non-exclusive, worldwide, perpetual, fully-paid-up, no-charge, irrevocable,
 * transferable and royalty-free right and license in its rights in the caBIG®
 * Software, including any copyright or patent rights therein, to (i) use,
 * install, disclose, access, operate, execute, reproduce, copy, modify,
 * translate, market, publicly display, publicly perform, and prepare
 * derivative works of the caBIG® Software in any manner and for any purpose,
 * and to have or permit others to do so; (ii) make, have made, use, practice,
 * sell, and offer for sale, import, and/or otherwise dispose of caBIG®
 * Software (or portions thereof); (iii) distribute and have distributed to and
 * by third parties the caBIG® Software and any modifications and derivative
 * works thereof; and (iv) sublicense the foregoing rights set out in (i), (ii)
 * and (iii) to third parties, including the right to license such rights to
 * further third parties. For sake of clarity, and not by way of limitation,
 * NCI shall have no right of accounting or right of payment from You or Your
 * sublicensees for the rights granted under this License. This License is
 * granted at no charge to You. Your downloading, copying, modifying,
 * displaying, distributing or use of caBIG® Software constitutes acceptance of
 * all of the terms and conditions of this Agreement. If you do not agree to
 * such terms and conditions, you have no right to download, copy, modify,
 * display, distribute or use the caBIG® Software.
 *
 * Your redistributions of the source code for the caBIG® Software must retain
 * the above copyright notice, this list of conditions and the disclaimer and
 * limitation of liability of Article 6 below. Your redistributions in object
 * code form must reproduce the above copyright notice, this list of conditions
 * and the disclaimer of Article 6 in the documentation and/or other materials
 * provided with the distribution, if any.
 *
 * Your end-user documentation included with the redistribution, if any, must
 * include the following acknowledgment: “This product includes software
 * developed by Danny Korenblum, Alan Snyder, Vitaliy Semeshko, Vladimir Kleper
 * and Pattanasak Mongkolwat, Northwestern University and Stanford University.”
 * If You do not include such end-user documentation, You shall include this
 * acknowledgment in the caBIG® Software itself, wherever such third-party
 * acknowledgments normally appear.
 *
 * You may not use the names “Northwestern University”, “Stanford University”,
 * “The National Cancer Institute”, “NCI”, “Cancer Bioinformatics Grid” or
 * “caBIG®” to endorse or promote products derived from this caBIG® Software.
 * This License does not authorize You to use any trademarks, service marks,
 * trade names, logos or product names of either caBIG® Participant, NCI or
 * caBIG®, except as required to comply with the terms of this License.
 *
 * For sake of clarity, and not by way of limitation, You are not prohibited by
 * this License from incorporating this caBIG® Software into Your proprietary
 * programs and into any third party proprietary programs. However, if You
 * incorporate the caBIG® Software into third party proprietary programs, You
 * agree that You are solely responsible for obtaining any permission from such
 * third parties required to incorporate the caBIG® Software into such third
 * party proprietary programs and for informing Your sublicensees, including
 * without limitation Your end-users, of their obligation to secure any
 * required permissions from such third parties before incorporating the caBIG®
 * Software into such third party proprietary software programs. In the event
 * that You fail to obtain such permissions, You agree to indemnify NCI for any
 * claims against NCI by such third parties, except to the extent prohibited by
 * law, resulting from Your failure to obtain such permissions.
 * For sake of clarity, and not by way of limitation, You may add Your own
 * copyright statement to Your modifications and to the derivative works, and
 * You may provide additional or different license terms and conditions in
 * Your sublicenses of modifications of the caBIG® Software, or any derivative
 * works of the caBIG® Software as a whole, provided Your use, reproduction,
 * and distribution of the Work otherwise complies with the conditions stated
 * in this License.
 *
 * THIS caBIG® SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES (INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE) ARE
 * DISCLAIMED. IN NO EVENT SHALL NCI OR THE NORTHWESTERN UNIVERSITY OR ITS
 * AFFILIATES BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS caBIG® SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

package edu.stanford.isis.atb.ui.view.widget.lexicon;

import static edu.stanford.isis.atb.ui.Const.FRM_LBL_CODE_MEANING;
import static edu.stanford.isis.atb.ui.Const.TPL_FORM_LABEL;

import java.awt.GridBagConstraints;
import java.awt.Insets;

import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.border.TitledBorder;

import edu.stanford.isis.atb.ui.Const;
import edu.stanford.isis.atb.ui.util.UIUtil;

/**
 * @author Vitaliy Semeshko
 */
public class LexiconTermView extends JPanel {

	private JTextField txtCodeMeaning = new JTextField();
	private JTextField txtCodeValue = new JTextField();
	private JTextField txtSchemaDesignator = new JTextField();
	private JTextField txtSchemaVersion = new JTextField();
	private JTextArea taDescription = new JTextArea();
	
	public LexiconTermView() {
		setBorder(new TitledBorder(Const.LBL_LEXICON_TERM));
	
		txtCodeMeaning.setEditable(false);
		txtCodeValue.setEditable(false);
		txtSchemaDesignator.setEditable(false);
		txtSchemaVersion.setEditable(false);
		taDescription.setEditable(false);
		taDescription.setLineWrap(true);
		
		setLayout(UIUtil.createFormLayout(5));
		
		GridBagConstraints gbcLabelCodeMeaning = new GridBagConstraints();
		gbcLabelCodeMeaning.insets = new Insets(10, 10, 5, 8);
		gbcLabelCodeMeaning.anchor = GridBagConstraints.EAST;
		gbcLabelCodeMeaning.gridx = 0;
		gbcLabelCodeMeaning.gridy = 0;
		add(label(String.format(TPL_FORM_LABEL, FRM_LBL_CODE_MEANING)), gbcLabelCodeMeaning);
		
		GridBagConstraints gbcTextCodeMeaning = new GridBagConstraints();
		gbcTextCodeMeaning.insets = new Insets(10, 0, 5, 10);
		gbcTextCodeMeaning.fill = GridBagConstraints.HORIZONTAL;
		gbcTextCodeMeaning.gridx = 1;
		gbcTextCodeMeaning.gridy = 0;
		add(txtCodeMeaning, gbcTextCodeMeaning);
		txtCodeMeaning.setColumns(10);
		
		GridBagConstraints gbcLabelCodeValue = new GridBagConstraints();
		gbcLabelCodeValue.anchor = GridBagConstraints.EAST;
		gbcLabelCodeValue.insets = new Insets(0, 10, 5, 8);
		gbcLabelCodeValue.gridx = 0;
		gbcLabelCodeValue.gridy = 1;
		add(label(Const.FRM_LBL_CODE_VALUE), gbcLabelCodeValue);
		
		GridBagConstraints gbcTextCodeValue = new GridBagConstraints();
		gbcTextCodeValue.insets = new Insets(0, 0, 5, 10);
		gbcTextCodeValue.fill = GridBagConstraints.HORIZONTAL;
		gbcTextCodeValue.gridx = 1;
		gbcTextCodeValue.gridy = 1;
		add(txtCodeValue, gbcTextCodeValue);
		txtCodeValue.setColumns(10);
		
		GridBagConstraints gbcLabelSchemaDesignator = new GridBagConstraints();
		gbcLabelSchemaDesignator.insets = new Insets(0, 10, 5, 8);
		gbcLabelSchemaDesignator.anchor = GridBagConstraints.EAST;
		gbcLabelSchemaDesignator.gridx = 0;
		gbcLabelSchemaDesignator.gridy = 2;
		add(label(Const.FRM_LBL_SCHEMA_DESIGNATOR), gbcLabelSchemaDesignator);
		
		GridBagConstraints gbcTextSchemaDesignator = new GridBagConstraints();
		gbcTextSchemaDesignator.insets = new Insets(0, 0, 5, 10);
		gbcTextSchemaDesignator.fill = GridBagConstraints.HORIZONTAL;
		gbcTextSchemaDesignator.gridx = 1;
		gbcTextSchemaDesignator.gridy = 2;
		add(txtSchemaDesignator, gbcTextSchemaDesignator);
		txtSchemaDesignator.setColumns(10);
		
		GridBagConstraints gbcLabelSchemaVersion = new GridBagConstraints();
		gbcLabelSchemaVersion.anchor = GridBagConstraints.EAST;
		gbcLabelSchemaVersion.insets = new Insets(0, 10, 0, 8);
		gbcLabelSchemaVersion.gridx = 0;
		gbcLabelSchemaVersion.gridy = 3;
		add(label(Const.FRM_LBL_SCHEMA_VERSION), gbcLabelSchemaVersion);
		
		GridBagConstraints gbcTextSchemaVersion = new GridBagConstraints();
		gbcTextSchemaVersion.insets = new Insets(0, 0, 5, 10);
		gbcTextSchemaVersion.fill = GridBagConstraints.HORIZONTAL;
		gbcTextSchemaVersion.gridx = 1;
		gbcTextSchemaVersion.gridy = 3;
		add(txtSchemaVersion, gbcTextSchemaVersion);
		txtSchemaVersion.setColumns(10);
		
		GridBagConstraints gbcLabelDescription = new GridBagConstraints();
		gbcLabelDescription.anchor = GridBagConstraints.NORTHEAST;
		gbcLabelDescription.insets = new Insets(0, 10, 0, 8);
		gbcLabelDescription.gridx = 0;
		gbcLabelDescription.gridy = 4;
		add(label(Const.FRM_LBL_DESCRIPTION), gbcLabelDescription);
		
		GridBagConstraints gbcTextDescription = new GridBagConstraints();
		gbcTextDescription.insets = new Insets(0, 0, 5, 10);
		gbcTextDescription.fill = GridBagConstraints.HORIZONTAL;
		gbcTextDescription.gridx = 1;
		gbcTextDescription.gridy = 4;
		add(new JScrollPane(taDescription), gbcTextDescription);
		taDescription.setColumns(10);
		taDescription.setRows(5);
	}
	
	private JLabel label(String text) {
		return new JLabel(String.format(Const.TPL_FORM_LABEL, text));
	}
	
	public void setCodeMeaning(String codeMeaning) {
		txtCodeMeaning.setText(codeMeaning);
		txtCodeMeaning.setCaretPosition(0);
	}
	
	public void setCodeValue(String codeValue) {
		txtCodeValue.setText(codeValue);
		txtCodeValue.setCaretPosition(0);
	}
	
	public void setSchemaDesignator(String schemaDesignator) {
		txtSchemaDesignator.setText(schemaDesignator);
		txtSchemaDesignator.setCaretPosition(0);
	}
	
	public void setSchemaVersion(String schemaVersion) {
		txtSchemaVersion.setText(schemaVersion);
		txtSchemaVersion.setCaretPosition(0);
	}
	
	public void setDescription(String description) {
		taDescription.setText(description);
		taDescription.setCaretPosition(0);
	}
	
	public void clear() {
		txtCodeMeaning.setText(Const.EMPTY);
		txtCodeValue.setText(Const.EMPTY);
		txtSchemaDesignator.setText(Const.EMPTY);
		txtSchemaVersion.setText(Const.EMPTY);
		taDescription.setText(Const.EMPTY);
	}
	
}
