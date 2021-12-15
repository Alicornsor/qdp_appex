grep UserID mstinitdumptmp.csv | head -n 1 > t_Sync_User.csv
grep -v UserID mstinitdumptmp.csv | grep -v t_Sync_User.csv | grep -v :: >> t_Sync_User.csv
scp t_Sync_User.csv mscffex@sqfm-knl1:./mstinit/dump/
ssh -n mscffex@sqfm-knl1 "echo users:;wc -l mstinit/dump/*"
