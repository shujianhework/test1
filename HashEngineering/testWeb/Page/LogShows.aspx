<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="LogShows.aspx.cs" Inherits="testWeb.Page.LogShows" %>

<%@ Register assembly="Microsoft.ReportViewer.WebForms, Version=11.0.0.0, Culture=neutral, PublicKeyToken=89845dcd8080cc91" namespace="Microsoft.Reporting.WebForms" tagprefix="rsweb" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
    <div>
    
        <asp:Button ID="Button1" runat="server" OnClick="Button1_Click" Text="清空" />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
        <asp:Button ID="Button2" runat="server" OnClick="Button2_Click" Text="刷新" />
        <asp:TextBox ID="TextBox1" runat="server" Width="457px"></asp:TextBox>
        <asp:Button ID="Button3" runat="server" OnClick="Button3_Click" Text="搜索" />
    </div>
        <asp:ListView ID="ListView1" runat="server" OnSelectedIndexChanged="ListView1_SelectedIndexChanged">
        </asp:ListView>
        <asp:TextBox ID="TextBox2" runat="server" Height="985px" TextMode="MultiLine" Width="1719px" style="margin-left: 1004px"></asp:TextBox>
    </form>
    </body>
</html>
