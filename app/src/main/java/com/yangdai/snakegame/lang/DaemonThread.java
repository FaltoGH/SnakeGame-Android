package com.yangdai.snakegame.lang;

public class DaemonThread extends Thread{
    public DaemonThread(){
        setDaemon(true);
    }

    public DaemonThread(Runnable target){
        super(target);
        setDaemon(true);
    }

}
