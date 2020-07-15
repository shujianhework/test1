using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace testWeb.Page
{
    public partial class ParamCheck : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            Dictionary<String, String> ret = new Dictionary<string, string>();
            try
            {
                String MainCheckFlg = Request["MainPack"];
                String TsdkUrl = Request["tsdk"];
                String CenterUrl = Request["center"];
                String Appid = Request["Appid"];
                String Channelid = Request["Channelid"];
                String Version = Request["version"];
                String OtherParam = Request["OtherParam"];
                if (OtherParam == null)
                {;
                    OtherParam = "";
                }
                if (Version == null)
                    Version = "0";
                Dictionary<int,Dictionary<string, object> > data = null;
                String cmd = "select * from packcheckitem where mainpack = '" + MainCheckFlg + "'";
                String sqlstr = @"Data Source = localhost; Initial Catalog = ClientTool; User Id = sa; Password = 123456;";
                ret["version"] = "1.0.0.0";
                if (Tools.DB.select(sqlstr,cmd, ref data) == false || data.Count < 1){
                    ret["error"] = "2";
                    ret["errstr"] = "查表失败,MainPack 不存在";
                }
                else
                {
                    ret["error"] = "-2";
                    ret["errstr"] = "MainPack existence Other Mismatch";
                    foreach (var item in data)
                    {
                        if (item.Value["tsdk"].Equals(TsdkUrl) && item.Value["center"].Equals(CenterUrl) && item.Value["appid"].ToString().Equals(Appid) && item.Value["channelid"].ToString().Equals(Channelid)) {
                            if (item.Value["script"] == null || item.Value["script"].ToString() == "")
                            {
                                String[] numvers = item.Value["version"].ToString().Split('.');
                                double num1 = 0;
                                foreach (var iitem in numvers)
                                {
                                    num1 = num1 * 10 + int.Parse(iitem);
                                }
                                String[] numvers2 = Version.Split('.');
                                double num2 = 0;
                                foreach (var iitem in numvers2)
                                {
                                    num2 = num2 * 10 + int.Parse(iitem);
                                }
                                if (num2 <= num1)
                                {
                                    //验证通过
                                    ret["error"] = "0";
                                    ret["errstr"] = "";
                                }
                                else
                                {
                                    ret["error"] = "-1";
                                    ret["errstr"] = "version > Item";
                                }
                            }
                            else
                            {

                                //让 lua 处理
                            }
                            break;
                        }
                    }
                }

            }
            catch (Exception ex)
            {
                ret.Clear();
                ret["error"] = "1";
                ret["errstr"] = ex.ToString();
            }
            finally
            {
                Response.Write(Tools.Tool.Object2Json(ret));
            }
        }
    }
}