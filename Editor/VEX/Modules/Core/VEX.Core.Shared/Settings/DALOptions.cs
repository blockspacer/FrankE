﻿#region License

// Copyright (c) 2013 Konrad Huber
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#endregion

using System;
using System.Reflection;
using System.ComponentModel.DataAnnotations;
using System.Collections.Generic;
using System.Text;
using System.ComponentModel;
using VEF.Model.Settings;
using System.Configuration;
using VEF.View.Types;
using VEF.DAL.Interface;

namespace VEF.DAL.Settings
{
    public class LocalizedDisplayNameAttribute : DisplayNameAttribute
    {
        private readonly PropertyInfo nameProperty;

        public LocalizedDisplayNameAttribute(string displayNameKey, Type resourceType = null)
            : base(displayNameKey)
        {
            if (resourceType != null)
            {
                nameProperty = resourceType.GetProperty(base.DisplayName,
                                               BindingFlags.Static | BindingFlags.Public);
            }
        }

        public override string DisplayName
        {
            get
            {
                if (nameProperty == null)
                {
                    return base.DisplayName;
                }
                return (string)nameProperty.GetValue(nameProperty.DeclaringType, null);
            }
        }
    }

    public class LocalizedCategoryAttribute : CategoryAttribute
    {
        private readonly PropertyInfo nameProperty;

        public LocalizedCategoryAttribute(string displayNameKey, Type resourceType = null)
            : base(displayNameKey)
        {
            if (resourceType != null)
            {
                nameProperty = resourceType.GetProperty(base.Category,
                                               BindingFlags.Static | BindingFlags.Public);
            }
        }

        protected override string GetLocalizedString(string value)
        {
            if (nameProperty == null)
            {
                return base.Category;
            }
            return (string)nameProperty.GetValue(nameProperty.DeclaringType, null);
        }

    }
    public class LocalizedDescriptionAttribute : DescriptionAttribute
    {
        private readonly PropertyInfo nameProperty;

        public LocalizedDescriptionAttribute(string displayNameKey, Type resourceType = null)
            : base(displayNameKey)
        {
            if (resourceType != null)
            {
                nameProperty = resourceType.GetProperty(base.Description,
                                               BindingFlags.Static | BindingFlags.Public);
            }
        }

        public override string Description
        {
            get
            {
                if (nameProperty == null)
                {
                    return base.Description;
                }
                return (string)nameProperty.GetValue(nameProperty.DeclaringType, null);
            }
        }
    }

    public class DataErrorInfoImpl : AbstractSettings, IDataErrorInfo
    {
        string IDataErrorInfo.Error { get { return string.Empty; } }

        string IDataErrorInfo.this[string columnName]
        {
            get
            {
                var pi = GetType().GetProperty(columnName);
                var value = pi.GetValue(this, null);

                var context = new ValidationContext(this, null, null) { MemberName = columnName };
                var validationResults = new List<ValidationResult>();
                if (!Validator.TryValidateProperty(value, context, validationResults))
                {
                    var sb = new StringBuilder();
                    foreach (var vr in validationResults)
                    {
                        sb.AppendLine(vr.ErrorMessage);
                    }
                    return sb.ToString().Trim();
                }
                return null;
            }
        }
    }

    /// <summary>
    /// Database Options
    /// </summary>
    public class DALOptions : DataErrorInfoImpl
    {
        private string m_IDName;
        private static DALOptions settings = new DALOptions();

        private DALOptions()
        {
        }

        public void SetIDName(String idName)
        {
            m_IDName = idName;
        }

        [Browsable(false)]
        public static DALOptions Default
        {
            get { return settings; }
        }

        [UserScopedSetting()]
        [DefaultSettingValue("")]
        [LocalizedCategory("Identity", typeof(VEF.Properties.Resources))]
        [LocalizedDisplayName("IDName", typeof(VEF.Properties.Resources))]
        [LocalizedDescriptionAttribute("IDNameDesc", typeof(VEF.Properties.Resources))]
        [Required(AllowEmptyStrings = false, ErrorMessage = "IDName is required")]
        [ReadOnly(true)]
        public string IDName
        {
            get { return m_IDName; }// (String)this["IDName"]; }
           // set { this["IDName"] = value; }
        }

        [UserScopedSetting()]
        [DefaultSettingValue("")]
        [LocalizedCategory("Datenbank", typeof(VEF.Properties.Resources))]
        [LocalizedDisplayName("Host", typeof(VEF.Properties.Resources))]
        [LocalizedDescriptionAttribute("HostDesc", typeof(VEF.Properties.Resources))]
        [Required(AllowEmptyStrings = false, ErrorMessage = "Host is required")]
        public string Host
        {
            get { return (String) this["Host"]; }
            set { this["Host"] = value; }
        }



        [UserScopedSetting()]
        [DefaultSettingValue("")]
        [LocalizedCategory("Datenbank", typeof(VEF.Properties.Resources))]
        [LocalizedDisplayName("DBName", typeof(VEF.Properties.Resources))]
        [LocalizedDescriptionAttribute("DBNameDesc", typeof(VEF.Properties.Resources))]
        public string Name
        {
            get { return (String)this["Name"]; }
            set { this["Name"] = value; }
        }


        [UserScopedSetting()]
        [DefaultSettingValue("")]
        [LocalizedCategory("Datenbank", typeof(VEF.Properties.Resources))]
        [LocalizedDisplayName("DBDescription", typeof(VEF.Properties.Resources))]
        [LocalizedDescriptionAttribute("DBDescriptionDesc", typeof(VEF.Properties.Resources))] 
        public string Description
        {
            get { return (String)this["Description"]; }
            set { this["Description"] = value; }
        }



        [UserScopedSetting()]
        [DefaultSettingValue("0")]
        [LocalizedCategory("Datenbank", typeof(VEF.Properties.Resources))]
        [LocalizedDisplayName("DBPort", typeof(VEF.Properties.Resources))]
        [LocalizedDescriptionAttribute("DBPortDesc", typeof(VEF.Properties.Resources))]  
        public UInt32 Port
        {
            get { return (UInt32)this["Port"]; }
            set { this["Port"] = value; }
        }


        [UserScopedSetting()]
        //     [DefaultSettingValue("White")]
        [LocalizedCategory("Datenbank", typeof(VEF.Properties.Resources))]
        [LocalizedDisplayName("DBServiceName", typeof(VEF.Properties.Resources))]
        [LocalizedDescriptionAttribute("DBServiceNameDesc", typeof(VEF.Properties.Resources))]
    
        public string ServiceName
        {
            get { return (String)this["ServiceName"]; }
            set { this["ServiceName"] = value; }
        }


        [UserScopedSetting()]
        [DefaultSettingValue("")]
        [LocalizedCategory("Datenbank", typeof(VEF.Properties.Resources))]
        [LocalizedDisplayName("DBUser", typeof(VEF.Properties.Resources))]
        [LocalizedDescriptionAttribute("DBUserDesc", typeof(VEF.Properties.Resources))]  
        public string User
        {
            get { return (String)this["User"]; }
            set { this["User"] = value; }
        }

        [UserScopedSetting()]
        [DefaultSettingValue("")]
        [LocalizedCategory("Datenbank", typeof(VEF.Properties.Resources))]
        [LocalizedDisplayName("DBPassword", typeof(VEF.Properties.Resources))]
        [LocalizedDescriptionAttribute("DBPasswordDesc", typeof(VEF.Properties.Resources))]    
        [PasswordPropertyText(true)]
        [Editor(typeof(PasswordEditor), typeof(PasswordEditor))]
        public string Password
        {
            get { return (String)this["Password"]; }
            set { this["Password"] = value; }
        }


        [UserScopedSetting()]
        [DefaultSettingValue("true")]
        [LocalizedCategory("Datenbank", typeof(VEF.Properties.Resources))]
        [LocalizedDisplayName("DBWinAuth", typeof(VEF.Properties.Resources))]
        [LocalizedDescriptionAttribute("DBWinAuthDesc", typeof(VEF.Properties.Resources))]   
        public bool WinAuth
        {
            get { return (Boolean)this["WinAuth"]; }
            set { this["WinAuth"] = value; }
        }


        [UserScopedSetting()]
        [DefaultSettingValue("MSSQL")]
        [LocalizedCategory("Datenbank", typeof(VEF.Properties.Resources))]
        [LocalizedDisplayName("DBType", typeof(VEF.Properties.Resources))]
        [LocalizedDescriptionAttribute("DBTypeDesc", typeof(VEF.Properties.Resources))]  
        public DBType DBType
        {
            get { return (DBType)this["DBType"]; }
            set { this["DBType"] = value; }
        }
       
        [UserScopedSetting()]
        [DefaultSettingValue("true")]
        [Browsable(false)]
        public bool LivePreview
        {
            get { return (bool) this["LivePreview"]; }
            set { this["LivePreview"] = value; }
        }


        [UserScopedSetting()]
        //[DefaultSettingValue(new Guid().ToString())]
        [Browsable(false)]
        public Guid Guid
        {
            get
            {
                if (this["Guid"] == null) { this["Guid"] = new Guid(); return (Guid)this["Guid"]; }
                else return (Guid)this["Guid"];
            }
            set { this["Guid"] = value; }
        }
    }
}