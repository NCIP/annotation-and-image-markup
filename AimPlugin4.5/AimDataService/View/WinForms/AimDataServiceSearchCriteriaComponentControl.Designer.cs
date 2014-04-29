namespace AimDataService.View.WinForms
{
    partial class AimDataServiceSearchCriteriaComponentControl
    {
        /// <summary> 
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(AimDataServiceSearchCriteriaComponentControl));
            this._resetButton = new System.Windows.Forms.Button();
            this._cancelButton = new System.Windows.Forms.Button();
            this._annotationOfAnnotationRadioButton = new System.Windows.Forms.RadioButton();
            this._titleBar = new Crownwood.DotNetMagic.Controls.TitleBar();
            this._imageAnnotationRadioButton = new System.Windows.Forms.RadioButton();
            this._patientNameTextField = new ClearCanvas.Desktop.View.WinForms.TextField();
            this._patientIdTextField = new ClearCanvas.Desktop.View.WinForms.TextField();
            this._annotationNameTextField = new ClearCanvas.Desktop.View.WinForms.TextField();
            this._advancedSearchCriteriaGroupBox = new System.Windows.Forms.GroupBox();
            this._addButton = new System.Windows.Forms.Button();
            this._valueTextField = new ClearCanvas.Desktop.View.WinForms.TextField();
            this._attributeLabel = new System.Windows.Forms.Label();
            this._attributeComboBox = new System.Windows.Forms.ComboBox();
            this._aimClassLabel = new System.Windows.Forms.Label();
            this._aimClassComboBox = new System.Windows.Forms.ComboBox();
            this._advancedSearchCriteriaListView = new System.Windows.Forms.ListView();
            this._searchCriteriaColumnHeader = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this._valueColumnHeader = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this._deleteCriteriaColumnHeader = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this._searchCriteriaLabel = new System.Windows.Forms.Label();
            this._searchButton = new System.Windows.Forms.Button();
            this._studyInstanceUidTextField = new ClearCanvas.Desktop.View.WinForms.TextField();
            this._imagingObservationCharacteristicsTextField = new ClearCanvas.Desktop.View.WinForms.TextField();
            this._imagingObservationsTextField = new ClearCanvas.Desktop.View.WinForms.TextField();
            this._userTextField = new ClearCanvas.Desktop.View.WinForms.TextField();
            this._imagingPhysicalEntityCharacteristicsTextField = new ClearCanvas.Desktop.View.WinForms.TextField();
            this._imagingPhysicalEntitiesTextField = new ClearCanvas.Desktop.View.WinForms.TextField();
            this._advancedSearchCriteriaGroupBox.SuspendLayout();
            this.SuspendLayout();
            // 
            // _resetButton
            // 
            this._resetButton.Location = new System.Drawing.Point(663, 112);
            this._resetButton.Margin = new System.Windows.Forms.Padding(2);
            this._resetButton.Name = "_resetButton";
            this._resetButton.Size = new System.Drawing.Size(90, 22);
            this._resetButton.TabIndex = 24;
            this._resetButton.Text = "Reset";
            this._resetButton.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
            this._resetButton.UseVisualStyleBackColor = true;
            this._resetButton.Click += new System.EventHandler(this.ResetButtonClick);
            // 
            // _cancelButton
            // 
            this._cancelButton.Location = new System.Drawing.Point(663, 84);
            this._cancelButton.Name = "_cancelButton";
            this._cancelButton.Size = new System.Drawing.Size(90, 22);
            this._cancelButton.TabIndex = 23;
            this._cancelButton.Text = "Cancel";
            this._cancelButton.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
            this._cancelButton.UseVisualStyleBackColor = true;
            this._cancelButton.Click += new System.EventHandler(this.CancelButtonClick);
            // 
            // _annotationOfAnnotationRadioButton
            // 
            this._annotationOfAnnotationRadioButton.AutoCheck = false;
            this._annotationOfAnnotationRadioButton.AutoSize = true;
            this._annotationOfAnnotationRadioButton.Location = new System.Drawing.Point(126, 187);
            this._annotationOfAnnotationRadioButton.Name = "_annotationOfAnnotationRadioButton";
            this._annotationOfAnnotationRadioButton.Size = new System.Drawing.Size(144, 17);
            this._annotationOfAnnotationRadioButton.TabIndex = 21;
            this._annotationOfAnnotationRadioButton.Text = "Annotation Of Annotation";
            this._annotationOfAnnotationRadioButton.UseVisualStyleBackColor = true;
            this._annotationOfAnnotationRadioButton.Visible = false;
            this._annotationOfAnnotationRadioButton.CheckedChanged += new System.EventHandler(this.AnnotationOfAnnotationRadioButtonCheckedChanged);
            // 
            // _titleBar
            // 
            this._titleBar.Dock = System.Windows.Forms.DockStyle.Top;
            this._titleBar.Font = new System.Drawing.Font("Arial", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this._titleBar.GradientColoring = Crownwood.DotNetMagic.Controls.GradientColoring.LightBackToDarkBack;
            this._titleBar.Location = new System.Drawing.Point(0, 0);
            this._titleBar.MouseOverColor = System.Drawing.Color.Empty;
            this._titleBar.Name = "_titleBar";
            this._titleBar.Size = new System.Drawing.Size(771, 30);
            this._titleBar.Style = Crownwood.DotNetMagic.Common.VisualStyle.IDE2005;
            this._titleBar.TabIndex = 19;
            this._titleBar.Text = "Search";
            // 
            // _imageAnnotationRadioButton
            // 
            this._imageAnnotationRadioButton.AutoCheck = false;
            this._imageAnnotationRadioButton.AutoSize = true;
            this._imageAnnotationRadioButton.Location = new System.Drawing.Point(16, 187);
            this._imageAnnotationRadioButton.Name = "_imageAnnotationRadioButton";
            this._imageAnnotationRadioButton.Size = new System.Drawing.Size(108, 17);
            this._imageAnnotationRadioButton.TabIndex = 20;
            this._imageAnnotationRadioButton.Text = "Image Annotation";
            this._imageAnnotationRadioButton.UseVisualStyleBackColor = true;
            this._imageAnnotationRadioButton.Visible = false;
            this._imageAnnotationRadioButton.CheckedChanged += new System.EventHandler(this.ImageAnnotationRadioButtonCheckedChanged);
            // 
            // _patientNameTextField
            // 
            this._patientNameTextField.LabelText = "Patient Name";
            this._patientNameTextField.Location = new System.Drawing.Point(254, 135);
            this._patientNameTextField.Margin = new System.Windows.Forms.Padding(2);
            this._patientNameTextField.Mask = "";
            this._patientNameTextField.Name = "_patientNameTextField";
            this._patientNameTextField.PasswordChar = '\0';
            this._patientNameTextField.Size = new System.Drawing.Size(211, 41);
            this._patientNameTextField.TabIndex = 31;
            this._patientNameTextField.ToolTip = null;
            this._patientNameTextField.Value = null;
            this._patientNameTextField.ValueChanged += new System.EventHandler(this.PatientNameTextFieldValueChanged);
            // 
            // _patientIdTextField
            // 
            this._patientIdTextField.LabelText = "Patient ID";
            this._patientIdTextField.Location = new System.Drawing.Point(16, 137);
            this._patientIdTextField.Margin = new System.Windows.Forms.Padding(2);
            this._patientIdTextField.Mask = "";
            this._patientIdTextField.Name = "_patientIdTextField";
            this._patientIdTextField.Size = new System.Drawing.Size(211, 41);
            this._patientIdTextField.TabIndex = 32;
            this._patientIdTextField.ToolTip = null;
            this._patientIdTextField.Value = null;
            this._patientIdTextField.ValueChanged += new System.EventHandler(this.PatientIdTextFieldValueChanged);
            // 
            // _annotationNameTextField
            // 
            this._annotationNameTextField.LabelText = "Annotation Name";
            this._annotationNameTextField.Location = new System.Drawing.Point(495, 135);
            this._annotationNameTextField.Margin = new System.Windows.Forms.Padding(2);
            this._annotationNameTextField.Mask = "";
            this._annotationNameTextField.Name = "_annotationNameTextField";
            this._annotationNameTextField.Size = new System.Drawing.Size(146, 41);
            this._annotationNameTextField.TabIndex = 33;
            this._annotationNameTextField.ToolTip = null;
            this._annotationNameTextField.Value = null;
            this._annotationNameTextField.ValueChanged += new System.EventHandler(this.AnnotationNameTextFieldValueChanged);
            // 
            // _advancedSearchCriteriaGroupBox
            // 
            this._advancedSearchCriteriaGroupBox.Controls.Add(this._addButton);
            this._advancedSearchCriteriaGroupBox.Controls.Add(this._valueTextField);
            this._advancedSearchCriteriaGroupBox.Controls.Add(this._attributeLabel);
            this._advancedSearchCriteriaGroupBox.Controls.Add(this._attributeComboBox);
            this._advancedSearchCriteriaGroupBox.Controls.Add(this._aimClassLabel);
            this._advancedSearchCriteriaGroupBox.Controls.Add(this._aimClassComboBox);
            this._advancedSearchCriteriaGroupBox.Location = new System.Drawing.Point(3, 223);
            this._advancedSearchCriteriaGroupBox.Name = "_advancedSearchCriteriaGroupBox";
            this._advancedSearchCriteriaGroupBox.Size = new System.Drawing.Size(770, 80);
            this._advancedSearchCriteriaGroupBox.TabIndex = 34;
            this._advancedSearchCriteriaGroupBox.TabStop = false;
            this._advancedSearchCriteriaGroupBox.Text = "Advanced Search Criteria";
            // 
            // _addButton
            // 
            this._addButton.Location = new System.Drawing.Point(660, 37);
            this._addButton.Name = "_addButton";
            this._addButton.Size = new System.Drawing.Size(90, 22);
            this._addButton.TabIndex = 35;
            this._addButton.Text = "Add";
            this._addButton.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
            this._addButton.UseVisualStyleBackColor = true;
            // 
            // _valueTextField
            // 
            this._valueTextField.LabelText = "Value";
            this._valueTextField.Location = new System.Drawing.Point(464, 20);
            this._valueTextField.Margin = new System.Windows.Forms.Padding(2);
            this._valueTextField.Mask = "";
            this._valueTextField.Name = "_valueTextField";
            this._valueTextField.Size = new System.Drawing.Size(145, 41);
            this._valueTextField.TabIndex = 34;
            this._valueTextField.ToolTip = null;
            this._valueTextField.Value = null;
            // 
            // _attributeLabel
            // 
            this._attributeLabel.AutoSize = true;
            this._attributeLabel.Location = new System.Drawing.Point(235, 21);
            this._attributeLabel.Name = "_attributeLabel";
            this._attributeLabel.Size = new System.Drawing.Size(46, 13);
            this._attributeLabel.TabIndex = 4;
            this._attributeLabel.Text = "Attribute";
            // 
            // _attributeComboBox
            // 
            this._attributeComboBox.FormattingEnabled = true;
            this._attributeComboBox.Location = new System.Drawing.Point(217, 38);
            this._attributeComboBox.Name = "_attributeComboBox";
            this._attributeComboBox.Size = new System.Drawing.Size(242, 21);
            this._attributeComboBox.TabIndex = 3;
            // 
            // _aimClassLabel
            // 
            this._aimClassLabel.AutoSize = true;
            this._aimClassLabel.Location = new System.Drawing.Point(6, 21);
            this._aimClassLabel.Name = "_aimClassLabel";
            this._aimClassLabel.Size = new System.Drawing.Size(54, 13);
            this._aimClassLabel.TabIndex = 2;
            this._aimClassLabel.Text = "AIM Class";
            // 
            // _aimClassComboBox
            // 
            this._aimClassComboBox.FormattingEnabled = true;
            this._aimClassComboBox.Location = new System.Drawing.Point(13, 38);
            this._aimClassComboBox.Name = "_aimClassComboBox";
            this._aimClassComboBox.Size = new System.Drawing.Size(198, 21);
            this._aimClassComboBox.TabIndex = 1;
            // 
            // _advancedSearchCriteriaListView
            // 
            this._advancedSearchCriteriaListView.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this._searchCriteriaColumnHeader,
            this._valueColumnHeader,
            this._deleteCriteriaColumnHeader});
            this._advancedSearchCriteriaListView.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.None;
            this._advancedSearchCriteriaListView.Location = new System.Drawing.Point(779, 65);
            this._advancedSearchCriteriaListView.Name = "_advancedSearchCriteriaListView";
            this._advancedSearchCriteriaListView.Size = new System.Drawing.Size(335, 154);
            this._advancedSearchCriteriaListView.TabIndex = 0;
            this._advancedSearchCriteriaListView.UseCompatibleStateImageBehavior = false;
            this._advancedSearchCriteriaListView.View = System.Windows.Forms.View.Details;
            // 
            // _searchCriteriaColumnHeader
            // 
            this._searchCriteriaColumnHeader.Text = "AIM Class";
            this._searchCriteriaColumnHeader.Width = 80;
            // 
            // _valueColumnHeader
            // 
            this._valueColumnHeader.Text = "Value";
            this._valueColumnHeader.Width = 120;
            // 
            // _deleteCriteriaColumnHeader
            // 
            this._deleteCriteriaColumnHeader.Text = "";
            // 
            // _searchCriteriaLabel
            // 
            this._searchCriteriaLabel.AutoSize = true;
            this._searchCriteriaLabel.Location = new System.Drawing.Point(782, 47);
            this._searchCriteriaLabel.Name = "_searchCriteriaLabel";
            this._searchCriteriaLabel.Size = new System.Drawing.Size(128, 13);
            this._searchCriteriaLabel.TabIndex = 35;
            this._searchCriteriaLabel.Text = "Advanced Search Criteria";
            // 
            // _searchButton
            // 
            this._searchButton.Image = ((System.Drawing.Image)(resources.GetObject("_searchButton.Image")));
            this._searchButton.Location = new System.Drawing.Point(663, 56);
            this._searchButton.Name = "_searchButton";
            this._searchButton.Size = new System.Drawing.Size(90, 22);
            this._searchButton.TabIndex = 22;
            this._searchButton.Text = "Search";
            this._searchButton.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
            this._searchButton.UseVisualStyleBackColor = true;
            this._searchButton.Click += new System.EventHandler(this.SearchButtonClick);
            // 
            // _studyInstanceUidTextField
            // 
            this._studyInstanceUidTextField.LabelText = "Study Instance UID";
            this._studyInstanceUidTextField.Location = new System.Drawing.Point(495, 92);
            this._studyInstanceUidTextField.Margin = new System.Windows.Forms.Padding(2);
            this._studyInstanceUidTextField.Mask = "";
            this._studyInstanceUidTextField.Name = "_studyInstanceUidTextField";
            this._studyInstanceUidTextField.Size = new System.Drawing.Size(146, 41);
            this._studyInstanceUidTextField.TabIndex = 41;
            this._studyInstanceUidTextField.ToolTip = null;
            this._studyInstanceUidTextField.Value = null;
            this._studyInstanceUidTextField.ValueChanged += new System.EventHandler(this.StudyInstanceUidTextFieldValueChanged);
            // 
            // _imagingObservationCharacteristicsTextField
            // 
            this._imagingObservationCharacteristicsTextField.LabelText = "Imaging Observation Characteristics";
            this._imagingObservationCharacteristicsTextField.Location = new System.Drawing.Point(254, 92);
            this._imagingObservationCharacteristicsTextField.Margin = new System.Windows.Forms.Padding(2);
            this._imagingObservationCharacteristicsTextField.Mask = "";
            this._imagingObservationCharacteristicsTextField.Name = "_imagingObservationCharacteristicsTextField";
            this._imagingObservationCharacteristicsTextField.Size = new System.Drawing.Size(211, 41);
            this._imagingObservationCharacteristicsTextField.TabIndex = 40;
            this._imagingObservationCharacteristicsTextField.ToolTip = null;
            this._imagingObservationCharacteristicsTextField.Value = null;
            this._imagingObservationCharacteristicsTextField.ValueChanged += new System.EventHandler(this.ImagingObservationCharacteristicsTextFieldValueChanged);
            // 
            // _imagingObservationsTextField
            // 
            this._imagingObservationsTextField.LabelText = "Imaging Observations";
            this._imagingObservationsTextField.Location = new System.Drawing.Point(16, 92);
            this._imagingObservationsTextField.Margin = new System.Windows.Forms.Padding(2);
            this._imagingObservationsTextField.Mask = "";
            this._imagingObservationsTextField.Name = "_imagingObservationsTextField";
            this._imagingObservationsTextField.Size = new System.Drawing.Size(211, 41);
            this._imagingObservationsTextField.TabIndex = 39;
            this._imagingObservationsTextField.ToolTip = null;
            this._imagingObservationsTextField.Value = null;
            this._imagingObservationsTextField.ValueChanged += new System.EventHandler(this.ImagingObservationsTextFieldValueChanged);
            // 
            // _userTextField
            // 
            this._userTextField.LabelText = "User";
            this._userTextField.Location = new System.Drawing.Point(495, 47);
            this._userTextField.Margin = new System.Windows.Forms.Padding(2);
            this._userTextField.Mask = "";
            this._userTextField.Name = "_userTextField";
            this._userTextField.Size = new System.Drawing.Size(146, 41);
            this._userTextField.TabIndex = 38;
            this._userTextField.ToolTip = null;
            this._userTextField.Value = null;
            this._userTextField.ValueChanged += new System.EventHandler(this.UserTextFieldValueChanged);
            // 
            // _imagingPhysicalEntityCharacteristicsTextField
            // 
            this._imagingPhysicalEntityCharacteristicsTextField.LabelText = "Imaging Physical Entity Characteristics";
            this._imagingPhysicalEntityCharacteristicsTextField.Location = new System.Drawing.Point(254, 47);
            this._imagingPhysicalEntityCharacteristicsTextField.Margin = new System.Windows.Forms.Padding(2);
            this._imagingPhysicalEntityCharacteristicsTextField.Mask = "";
            this._imagingPhysicalEntityCharacteristicsTextField.Name = "_imagingPhysicalEntityCharacteristicsTextField";
            this._imagingPhysicalEntityCharacteristicsTextField.Size = new System.Drawing.Size(211, 41);
            this._imagingPhysicalEntityCharacteristicsTextField.TabIndex = 37;
            this._imagingPhysicalEntityCharacteristicsTextField.ToolTip = null;
            this._imagingPhysicalEntityCharacteristicsTextField.Value = null;
            this._imagingPhysicalEntityCharacteristicsTextField.ValueChanged += new System.EventHandler(this.ImagingPhysicalEntityCharacteristicsTextFieldValueChanged);
            // 
            // _imagingPhysicalEntitiesTextField
            // 
            this._imagingPhysicalEntitiesTextField.LabelText = "Imaging Physical Entities";
            this._imagingPhysicalEntitiesTextField.Location = new System.Drawing.Point(16, 47);
            this._imagingPhysicalEntitiesTextField.Margin = new System.Windows.Forms.Padding(2);
            this._imagingPhysicalEntitiesTextField.Mask = "";
            this._imagingPhysicalEntitiesTextField.Name = "_imagingPhysicalEntitiesTextField";
            this._imagingPhysicalEntitiesTextField.Size = new System.Drawing.Size(211, 41);
            this._imagingPhysicalEntitiesTextField.TabIndex = 36;
            this._imagingPhysicalEntitiesTextField.ToolTip = null;
            this._imagingPhysicalEntitiesTextField.Value = null;
            this._imagingPhysicalEntitiesTextField.ValueChanged += new System.EventHandler(this.ImagingPhysicalEntitiesTextFieldValueChanged);
            // 
            // AimDataServiceSearchCriteriaComponentControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this._studyInstanceUidTextField);
            this.Controls.Add(this._imagingObservationCharacteristicsTextField);
            this.Controls.Add(this._imagingObservationsTextField);
            this.Controls.Add(this._userTextField);
            this.Controls.Add(this._imagingPhysicalEntityCharacteristicsTextField);
            this.Controls.Add(this._imagingPhysicalEntitiesTextField);
            this.Controls.Add(this._searchCriteriaLabel);
            this.Controls.Add(this._advancedSearchCriteriaGroupBox);
            this.Controls.Add(this._annotationNameTextField);
            this.Controls.Add(this._patientIdTextField);
            this.Controls.Add(this._patientNameTextField);
            this.Controls.Add(this._advancedSearchCriteriaListView);
            this.Controls.Add(this._resetButton);
            this.Controls.Add(this._cancelButton);
            this.Controls.Add(this._annotationOfAnnotationRadioButton);
            this.Controls.Add(this._searchButton);
            this.Controls.Add(this._titleBar);
            this.Controls.Add(this._imageAnnotationRadioButton);
            this.Name = "AimDataServiceSearchCriteriaComponentControl";
            this.Size = new System.Drawing.Size(771, 220);
            this._advancedSearchCriteriaGroupBox.ResumeLayout(false);
            this._advancedSearchCriteriaGroupBox.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button _resetButton;
        private System.Windows.Forms.Button _cancelButton;
        private System.Windows.Forms.RadioButton _annotationOfAnnotationRadioButton;
        private System.Windows.Forms.Button _searchButton;
        private Crownwood.DotNetMagic.Controls.TitleBar _titleBar;
        private System.Windows.Forms.RadioButton _imageAnnotationRadioButton;
        private ClearCanvas.Desktop.View.WinForms.TextField _patientNameTextField;
        private ClearCanvas.Desktop.View.WinForms.TextField _patientIdTextField;
        private ClearCanvas.Desktop.View.WinForms.TextField _annotationNameTextField;
        private System.Windows.Forms.GroupBox _advancedSearchCriteriaGroupBox;
        private System.Windows.Forms.ListView _advancedSearchCriteriaListView;
        private System.Windows.Forms.ComboBox _aimClassComboBox;
        private System.Windows.Forms.Label _attributeLabel;
        private System.Windows.Forms.ComboBox _attributeComboBox;
        private System.Windows.Forms.Label _aimClassLabel;
        private ClearCanvas.Desktop.View.WinForms.TextField _valueTextField;
        private System.Windows.Forms.Button _addButton;
        private System.Windows.Forms.ColumnHeader _searchCriteriaColumnHeader;
        private System.Windows.Forms.ColumnHeader _valueColumnHeader;
        private System.Windows.Forms.ColumnHeader _deleteCriteriaColumnHeader;
        private System.Windows.Forms.Label _searchCriteriaLabel;
        private ClearCanvas.Desktop.View.WinForms.TextField _studyInstanceUidTextField;
        private ClearCanvas.Desktop.View.WinForms.TextField _imagingObservationCharacteristicsTextField;
        private ClearCanvas.Desktop.View.WinForms.TextField _imagingObservationsTextField;
        private ClearCanvas.Desktop.View.WinForms.TextField _userTextField;
        private ClearCanvas.Desktop.View.WinForms.TextField _imagingPhysicalEntityCharacteristicsTextField;
        private ClearCanvas.Desktop.View.WinForms.TextField _imagingPhysicalEntitiesTextField;
    }
}
