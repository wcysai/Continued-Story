for(int iter=1;iter<=10;iter++)
    {
        for(int i=1;i<=n;i++) 
        {
            if(stopping[i]) lmost[i]=i;
            else lmost[i]=lmost[i-1];
        }
        for(int i=n;i>=1;i--)
        {
            if(stopping[i]) rmost[i]=i;
            else rmost[i]=rmost[i+1];
        }
        for(int i=1;i<=n;i++)
        {
            if(stopping[i]&&i!=1&&i!=n)
            {
                int l=lmost[i],r=rmost[i];
                if((r-i)*a[l]+(i-l)*a[r]<=(r-l)*a[i]) stopping[i]=false; 
            }
        }
    }