package com.yangdai.snakegame.lang;

public class DaemonThread extends Thread{
    public DaemonThread(){
        setDaemon(true);
    }
}
