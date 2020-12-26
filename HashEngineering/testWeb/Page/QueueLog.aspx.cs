using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace testWeb.Page
{
    //队列日志记录 部分使用
    public partial class QueueLog : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            try
            {
                String Head = this.Request["head"];
                String data = this.Request["data"];
                String CloseQueueLog = this.Request["cql"];
                String PAS = this.Request["pas"];
                String ip = Tools.Tool.GetIp(this.Request);

                if (Head != null && data != null)
                {
                    try
                    {
                        Dictionary<String, object> dir = (Dictionary<String, object>)Tools.Tool.Json2Object(Head);
                        if (dir["version"].Equals(null))
                            Tools.Log.Queuewrite("head:" + Head + "ip:" + ip + "\ndata:" + data);
                        else
                        {
                            switch (dir["version"].ToString())
                            {
                                case "1.0":
                                    {
                                        String path = dir["tag"].ToString()+"_"+dir["pack"].ToString();
                                        Tools.Log.Queuewrite("ip:" + ip + "\ndata:" + data, path);
                                    }
                                    break;
                                default:
                                    {
                                        Response.Write("version out index");
                                    }
                                    return;
                            }
                        }
                        
                    }
                    catch (Exception ex)
                    {
                        Response.Write("Head Json error " + ex.ToString());
                    }
                    finally
                    {
                    }
                }
                else if (PAS != null && PAS.Equals("tsixi123logABC!!)") && CloseQueueLog != null)
                {
                    if (CloseQueueLog.Equals("True"))
                        Tools.Log.setSwitchWriteLog(true);
                    else if (CloseQueueLog.Equals("Flase"))
                        Tools.Log.setSwitchWriteLog(false);
                }
                else
                {
                    Response.Write(Tools.Log.getSwitchWriteLog());
                }
            }
            catch (Exception ex)
            {
                Response.Write(ex.ToString());
            }
        }
    }
}