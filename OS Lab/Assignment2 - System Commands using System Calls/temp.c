case 2:
                {
                    printf("\nFCFS\n");
                    int no_of_process;
                    printf("\nNumber of Processes :");
                    scanf(" %d",&no_of_process);
                    int arrival[no_of_process] ,burst[no_of_process], turnaround[no_of_process], waiting[no_of_process],totalwaitingtime=0,totalturnaround=0;
                    char pid[no_of_process][5];
                    for(int i=0;i<no_of_process;i++)
                    {
                        printf("\nProcess ID: ");
                        scanf(" %s",pid[i]);
                        printf("\nArrival Time :");
                        scanf(" %d",&arrival[i]);
                        printf("\nBurst Time :");
                        scanf(" %d",&burst[i]);
                    //     if(i==0)
                    //     {
                    //         waiting[i] =0;
                    //     }
                    //     else
                    //     {
                    //         waiting[i] =  burst[i-1] + waiting[i-1];
                    //     }
                        
                    //     turnaround[i] = burst[i] + waiting[i];
                    //     totalwaitingtime+=waiting[i];
                    //     totalturnaround+=turnaround[i];
                    }
                    int pos;
                    int tempburst;
                    char temppid[3];
                    for(int i=0;i<no_of_process;i++)
                    {
                        pos=i;
                        for(j=i+1;j<n;j++)
                        {
                            if(burst[j]<burst[pos])
                            pos=j;
                        }
                 
                        tempburst=burst[i];
                        burst[i]=burst[pos];
                        burst[pos]=tempburst;

                        
                        temppid=pid[i];
                        pid[i]=pid[pos];
                        pid[pos]=temppid;
                    }
                    for(i=1;i<n;i++)
                    {
                        waiting[i]=0;
                        for(j=0;j<i;j++)
                            waiting[i]+=burst[j];
                        totalwaitingtime+=waiting[i];
                        turnaround[i]=burst[i]+waiting[i];
                        totalturnaround+=turnaround[i];
                    }
                    printf("\nP_ID  Arrival_Time  Burst_Time  Turnaround_Time  Waiting Time");
                    for(int i=0;i<no_of_process;i++)
                    {
                        printf("\n %3s %7d %11d %11d %15d",pid[i], arrival[i], burst[i], turnaround[i], waiting[i]);
                    }
    
                    float avgwaiting=(float)(totalwaitingtime/no_of_process);
                    float avgturnaround=(float)(totalturnaround/no_of_process);
                    printf("\n\t\tAVERAGE  AverageWaitingTime=%.2f\tAverageTurnaroundTime=%.2f\n",avgwaiting,avgturnaround);
                }