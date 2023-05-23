var=$(ps -ef|grep 'webserv'|grep -v 'grep'|grep -v $0)
pid=$(echo ${var} | cut -d " " -f2)
 
if [ -n "${pid}" ]
then
    kill ${pid} & > /dev/null
 
fi
