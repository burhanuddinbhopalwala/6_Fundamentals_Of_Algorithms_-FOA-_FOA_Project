#include<dos.h>
#include<stdio.h>
#include<conio.h>
#include<limits.h>
#include<iostream.h>
#include<graphics.h>
#include<stdlib.h>
#define V 8
#define INF 999

// Global declarations
int pathv = 0;
int path[10];


// QuickSort Algorithm
class QuickSort
{
	public:
	void swap( int[] , int , int );
	int partition( int[] , int , int );
	//int randomizedPartition( int[] , int , int );// Average Case
	void quickSort( int[] , int , int );
};

void QuickSort::swap( int array[] , int index1 , int index2 )
{
	int temp;
	temp = array[index1];
	array[index1] = array[index2];
	array[index2] = temp;
}

int QuickSort::partition( int array[] , int start , int end )
{
	int pivot = array[end];
	int pIndex = start; // pIndex -> partitionIndex

	for( int i = start ; i < end ; i++ )
	{
		if( array[i] <= pivot )
		{
			swap( array , i , pIndex );
// Direct swap function not work as it does not change the array .
			++pIndex;
		}
	}

	swap( array , pIndex , end );
	return pIndex;
}

void QuickSort::quickSort( int array[] , int start , int end )
{

	if( start >= end )
		return;

	int pIndex = partition( array , start , end );

	quickSort( array , start , pIndex-1);
	quickSort( array , pIndex+1 , end );
// NOTE :- We working on same array through out .
}

/*-----------------------------------END-------------------------------------
-------------------------------Dijkstras Starts-----------------------------*/

int printFinalShortestPath( int path[] , int pathv , int dest , int i )
{
	cout<<"Wait finding your shortest path using Recursion .... : ";
	delay(1500);
	for( int k = i-1 ; k>=0 ; k-- )
		cout<<path[k]<<" - ";
			cout<<dest;
	cout<<" \nMinimum Path Value : "<<pathv;
	return pathv;
}

// calculating final shortest path of MST using Backtracking
int calculateFinalShortestPath( int parent[] , int distance[] , int source ,
				int dest , int i , int j )
{
	if( j == 0 )
		return printFinalShortestPath( path , pathv , dest , i );

			pathv = pathv + distance[j];
			j = parent[j];
			pathv = pathv - distance[j];
			path[i] = j;
			++i;
			return calculateFinalShortestPath( parent ,
			distance , source , dest , i , j ); // Recursion
}

void findDesiredPath( int graph[V][V] , int parent[] , int path[] ,
		int pathv_min , int dest , int obstacle , int mpathv )
{
	int i = 0 ;
	pathv = 0 ; // It changes while cal shortest path and hence re-init .
	pathv = pathv + graph[obstacle][dest];
	path[i++] = obstacle ;

	int j = obstacle ;
	while( j != 0 )      // 0 is src
	{
		//pathv = pathv + graph[j][parent[j]];
		j = parent[j];
		path[i] = j;
		++i;
	}

	for( int k = i-1 ; k > 0 ; k-- )
		pathv = pathv + graph[path[k]][path[k-1]];

		if( pathv == mpathv )
			cout<<"\nIt is MST . ";

		else if( pathv < mpathv )
		{
			cout<<"Finding your desired path : ";
			delay(1500);

			for( int k = i-1 ; k>=0 ; k-- )
				cout<<path[k]<<" - ";

			cout<<dest;
			cout<<"\nyou are in MST upto : "<<path[++k];
			cout<<"\nDesire path value : "<<(pathv);
			cout<<"\nExtra path travel : "<<(pathv-pathv_min);

			if( mpathv == INT_MAX )
				cout<<"\nThink twice!!!!";
		}
}

int findDesiredPathWithoutObstacle( int graph[V][V] , int parent[] , int path[] ,
		int pathv_min , int dest , int obstacle )
{
	int i = 0 ;
	int jj;
	int pathi[5];
	int pathvi;

	for( int kkk = 1 ; kkk < 8 ; kkk++ )
	{
		if( obstacle == kkk )
			continue;

		else
		{
			i = 0;
			pathv = 0 ; // It changes while cal shortest path and hence re-init .
			pathv = pathv + graph[kkk][dest];

			for( int k = jj-1 ; k>=0 ; k-- )
				pathi[(jj-1)-(k)] = path[k];

			path[i++] = kkk ;

			int j = kkk ;
			while( j != 0 )      // 0 is src
			{
				//pathv = pathv + graph[j][parent[j]];
				j = parent[j];
				path[i] = j;
				++i;
			}

			pathvi = pathv;
			for( int kk = i-1 ; kk > 0 ; kk-- )
				pathv = pathv + graph[path[kk]][path[kk-1]];

			if ( pathv == pathv_min )
				break;

			jj=i ;

		}
	}

			cout<<"Finding your desired path : ";
			delay(1500);

			for( int k = jj-1 ; k>=0 ; k-- )
				cout<<pathi[k]<<" - ";

			cout<<dest;
			cout<<"\nyou are in MST upto : "<<pathi[++k];
			cout<<"\nDesire path value : "<<(pathvi);
			cout<<"\nExtra path travel : "<<(pathvi-pathv_min);

			return 0;
}

void findAllFilterPath( int graph[V][V] , int parent[] , int path[] ,
		int pathv_min , int dest , int mpathv )
{
	if( mpathv > pathv_min )
	{
		for( int i = 0 ; i< dest ; i++ ) // 0 for src
		{
			cout<<"\n";
			findDesiredPath( graph , parent , path , pathv_min , dest ,
			i , mpathv );
			cout<<"\n";
		}
	}
	else if( mpathv == pathv_min )
		cout<<"\nOnly the above MST is possible . ";
	else
		cout<<"\nSorry no path is possible .";
}

// finding minimum distance vertex from given vertex
int findMinimumDistanceVertex( int distance[] , int visit[])
{
   int min = INT_MAX, min_index;

   for (int v = 0; v < V; v++)
     if (visit[v] == 0 && distance[v] <= min)
	 min = distance[v], min_index = v;

   return min_index;
}

// for printing the MST
void printMST(int parent[] , int distance[], int source , int graph[V][V] )
{
   cout<<"MST with respect to "<<source<<" source";
   cout<<"\nVertex   Distance from Source\n";

   for (int i = 0; i < V; i++)
      cout<<parent[i]<<"--"<<i<<"\t\t"<<distance[i]<<"\n";

	// Without Obstacles :
	int dest , pathv_min;
	cout<<"\nWithout Obstacles : ";
	cout<<"\nEnter your destination from "<<source<<" source : ";
	cin>>dest;
	int j;
	j = dest;
	i = 0 ;// do not comment
		if( dest > 0 && dest < V )
			pathv_min = calculateFinalShortestPath( parent ,
				distance , source , dest , i , j );
		else
			cout<<"Invalid Destination try again!!!! ";

	// With Obstacles :
	int obstacle;
	int choice;
	cout<<"\n\nWith Obstacles : ";
	cout<<"\nEnter your obstacle : ";
	cin>>obstacle;
	cout<<"Enter 1 for in and 0 for out : ";
	cin>>choice;
	int path_exist = 0 ;


	if( dest > 0 && dest < V && obstacle > 0 && obstacle != dest &&
	choice > -1 && choice < 2 )
	{
		if ( choice == 1 )    // via obstacle
		{
			if( graph[obstacle][dest] ) // direct edge exist
				path_exist = 1;

			else if( path_exist == 0 )   // direct edge not exist
			{
				for( int k = 0 ; k < V ; k++ )
					if( obstacle == parent[k])
						break;

				if( graph[k][dest] )
				{
					path_exist = 2 ;

			findDesiredPath( graph , parent , path , pathv_min ,
				dest , k , INT_MAX );
				}// if( graph[k][dest])
			     }// else if
			else
				cout<<"Path Not Possible";


			if( path_exist == 1 )

			findDesiredPath( graph , parent , path , pathv_min ,
				dest , obstacle , INT_MAX );

			int mpathv;
			cout<<"\n\nEnter a Maximum path lenght : ";
			cin>>mpathv;
			findAllFilterPath( graph , parent , path , pathv_min ,
				dest , mpathv );


		}// if( choice == 1 )
		else                  // other than obstacle
				/*findDesiredPathWithoutObstacle( graph , parent ,
				path , pathv_min , dest , obstacle );  */
				cout<<"Coming Soon!!!";
	}
	else
		cout<<"Invalid data entered!!!!!";

}

//dijkstra implementation
void dijkstra(int graph[V][V], int source)
{
     int distance[V];
     int parent[V];
     int visit[V];

     for (int i = 0; i < V; i++)
	distance[i] = INT_MAX, visit[i] = 0;

     distance[source] = 0;
     parent[source] = -1;

     for (int count = 0; count < V-1; count++)
     {
       int u = findMinimumDistanceVertex( distance , visit );
       visit[u] = 1;

       for (int v = 0; v < V; v++)
	 if (!visit[v] && graph[u][v] && distance[u] != INT_MAX
				       && distance[u]+graph[u][v] < distance[v])
	 {
	    distance[v] = distance[u] + graph[u][v];
	    parent[v] = u;
	 }
     }
     printMST(parent , distance , source , graph );
}

/*-------------------------------------END-----------------------------------
---------------------------------Kruskles Starts----------------------------*/
int k_parent[10];

int find(int i)
{
	while(k_parent[i])
	i=k_parent[i];
	return i;
}

int uni(int i,int j)
{
	if(i!=j)
	{
		k_parent[j]=i;
		return 1;
	}
	return 0;
}

   void kruskal(int graph[8][8],int n)
   {
	int i,j,k,a,b,u,v,ne=1,min,mincost=0 ;
	int source = 0 , dest , pathv_min ;
	int minn[V] , l = 1 ;
	int k_distance[V]; // distance from source for all the vertex .
	int graphr[V][V];

	k_distance[source] = 0;
	minn[source] = 0;

	for( i = 0 ; i < V ; i++ )
		for( j = 0 ; j < V ; j++ )
			graphr[i][j] = graph[i][j];

	printf("\n\n\tImplementation of Kruskal's algorithm\n\n");

	for(i=0;i<V;i++)
	{
		for(j=0;j<V;j++)
		{
			if(graphr[i][j]==0)
			graphr[i][j]=INF;
		}
	}

	printf("\nThe edges of Minimum Cost Spanning Tree are\n\n");
	while(ne<n)
	{
		for(i=0 , min = INF ;i<n;i++)
		{
			for(j=0;j<n;j++)
			{
				if(graphr[i][j]<min)
				{
					min=graphr[i][j];
					a=u=i;
					b=v=j;
				}
			}
		}

		u=find(u);
		v=find(v);

		if(uni(u,v))
		{
			printf("\n%d edge (%d,%d) =%d\n",ne++,a,b,min);
			mincost +=min ;
			minn[b] = min ; // end point determines corresponding
			// edge distance
		}

		graphr[a][b]=graphr[b][a]=999;
	}

	k_parent[V-1] = 6 ; // updating the last parent;
	printf("\n\tMinimum cost = %d\n",mincost);

	for( i = 1 ; i < V ; i ++ )
		k_distance[i] = minn[i] + k_distance[k_parent[i]];

	getch();
	clrscr();
	cout<<"\nFinding Shortest path using Kruskal Algorithm : ";
	cout<<"\n\nEnter your destination from "<<source<<" source : ";
	cin>>dest;
	//int j;
	j = dest;
	i = 0 ;// do not comment
	pathv = 0; // Better for producing the correct results every time .
		if( dest > 0 && dest < V )
			pathv_min = calculateFinalShortestPath( k_parent ,
				k_distance , source , dest , i , j );
		else
			cout<<"Invalid Destination try again!!!! ";
}

/*-----------------------------------END--------------------------------------
----------------------------Floyd Warshall Starts----------------------------*/

int min(int,int);
int fpath[V][V];
int count = 0 ;

void findFloydShortestPath( int fsource, int fdest )
{
		if( fpath[fsource][fdest] != 0 )
		{
			findFloydShortestPath( fsource, fpath[fsource][fdest] );
			cout<<"-via-"<<fpath[fsource][fdest];
			findFloydShortestPath(fpath[fsource][fdest] , fdest );
			return;
		}
	//no intermediate nodes
		else
			return;
}


void AliterfindFloydShortestPath( int fsource, int fdest , int fobstacle )
{
		if( fpath[fsource][fdest] != 0 && count == 0 )
		{
			AliterfindFloydShortestPath( fsource, fpath[fsource][fdest] , fobstacle );
			if( fpath[fsource][fdest] != fobstacle )
				cout<<"-via-"<<fpath[fsource][fdest];
			else
			{
				++count;
				return;
			}
			AliterfindFloydShortestPath(fpath[fsource][fdest] , fdest , fobstacle );
			return;
		}
	//no intermediate nodes
		else
			return;
}

/*algoritm code*/

void printFloydSolution(int dist[][V])
{
    printf ("Following matrix shows the shortest distances"
	    " between every pair of vertices \n");
    for (int i = 0; i < V; i++)
    {
	for (int j = 0; j < V; j++)
	{
	    if (dist[i][j] == INF)
		printf("%7s", "INF");
	    else
		printf ("%7d", dist[i][j]);
	}
	printf("\n");
    }
}


void floydWarshell(int graph[][V])
{

    int dist[V][V],i, j, k;
    int station[V];
    int fsource,fdest;
    int u = 0 ;
    int vertex , fobstacle;

    cout<<"Floyd Warshall Algorithm : \n";

    for (i = 0; i < V; i++)
	for (j = 0; j < V; j++)
	    dist[i][j] = graph[i][j];


    for (i = 0; i < V; i++)
	for (j = 0; j < V; j++)
	    fpath[i][j] = 0;

    for (k = 0; k < V; k++)
    {
	for (i = 0; i < V; i++)
	{
	    for (j = 0; j < V; j++)
	    {
		if (dist[i][k] + dist[k][j] < dist[i][j])
		{
			 dist[i][j] = dist[i][k] + dist[k][j];
			 fpath[i][j] = k;
		}
		       // 	afpath[i][j] = k;
	    }
	}
    }

    printFloydSolution(dist);

    cout<<"\n\nFind your shortest path here : ";
    cout<<"\nEnter the source : ";
    cin>>fsource;
    cout<<"Enter the destination : ";
    cin>>fdest;
    cout<<fsource;
    findFloydShortestPath( fsource , fdest  );
    cout<<"-via-"<<fdest;
    cout<<"\nThe path value is : "<<dist[fsource][fdest]<<"\n";



    cout<<"\n\nEnter any vertex(0-7) to find the nearest station from : ";
    cin>>vertex;
	for( i = 0 ; i < 8 ; i++ )
		station[i] = dist[vertex][i];

	QuickSort q;
	q.quickSort( station , 0 , 7 );

	for( i = 0 ; i < V ; i++ )
	{
		if(  dist[vertex][i] == station[1] )
		{
			cout<<"Your nearest station from "<<vertex<<" is "<<i<<"th station";
			break;
		}
	}

	cout<<"\n\nWith Obstacle ";
	cout<<"\nEnter Your Obstacle : ";
	cin>>fobstacle;
	cout<<"Your one of the possible path is : \n"<<fsource;
	findFloydShortestPath( fsource , fobstacle  );
	cout<<"-via-"<<fobstacle;
	findFloydShortestPath( fobstacle , fdest  );
	cout<<"-via-"<<fdest;
	cout<<"\nThe path value is : "<<(dist[fsource][fobstacle]+dist[fobstacle][fdest])<<"\n";

	cout<<"\n\nWithout Obstacle ";
	cout<<"\nEnter Your Obstacle : ";
	cin>>fobstacle;
	cout<<"Your possible path is : \n";
		for( i = 0 ; i < V ; i ++ )
		{
			if( i != fsource && i != fdest && i != fobstacle )
			{
				cout<<"\nPossible paths are : \n"<<fsource;
				AliterfindFloydShortestPath( fsource , i , fobstacle );
				cout<<"-via-"<<i;
				AliterfindFloydShortestPath( i , fdest , fobstacle );
				cout<<"-via-"<<fdest;
				cout<<"\nThe path value is : ";
				cout<<(dist[fsource][i]+dist[i][fdest])<<"\n";
				delay(1200);
			}
		}
}
/*------------------------------------END------------------------------------
----------------------------------------------------------------------------*/

int ka=0;
void welcome();
void welcome_screen();
void loading_screen();
int main()
{

	clrscr();
		if(ka==0)
	       {

			welcome();
			++ka;
		}

	    clrscr();
		int choice;

	cout<<"\nEnter 1 for Dijkstras Algorithm";
	cout<<"\nEnter 2 for Floyd Warshall Algorithm";
	cout<<"\nEnter 3 Kruskal Algorithm";
	cout<<"\nEnter 4 for Final Analysation";
	cout<<"\nEnter 5 for Exit";

	int graph[V][V] = {   //8*8 matrix
		      {0, 1, 2, 3, 40, 50, 60, 70},
		      {1, 0, 12, 13, 6, 0, 0, 17},
		      {2, 12, 0, 23, 0, 5, 0, 27},
		      {3, 13, 23, 0, 0, 0, 4, 37},
		      {40, 6, 0, 0, 0, 45, 46, 47},
		      {50, 0, 5, 0, 45, 0, 56, 57},
		      {60, 0, 0, 4, 46, 56, 0, 7},
		      {70, 17, 27, 37, 47, 57, 7, 0},
		     };

    cout<<"\n\nEnter your choice : ";
    cin>>choice;
    switch( choice )
    {
	case 1 :
	{
			loading_screen();
			clrscr();
			int src;
			cout<<"\nDijkstra Algorithm (My Part)";
			cout<<"\nEnter your source : ";
			cin>>src;
			dijkstra( graph , src );
			cout<<"\nDo you want to continue(1/0) : ";
			cin>>choice;
		if( choice == 1 )
			main();
		else
			exit(0);
		break;

	}
	case 2 :
	{
		loading_screen();
		clrscr();
		int q,r;
		int graph[V][V] = {   //8*8 matrix  //Same as above matrix .
		      {0, 1, 2, 3, 40, 50, 60, 70},
		      {1, 0, 12, 13, 6, INF, INF, 17},
		      {2, 12, 0, 23, INF, 5, INF, 27},
		      {3, 13, 23, 0, INF, INF, 4, 37},
		      {40, 6, INF, INF, 0, 45, 46, 47},
		      {50, INF, 5, INF, 45, 0, 56, 57},
		      {60, INF, INF, 4, 46, 56, 0, 7},
		      {70, 17, 27, 37, 47, 57, 7, 0},
		     };
		floydWarshell(graph);
		cout<<"\nDo you want to continue(1/0) : ";
		cin>>choice;
		if( choice == 1 )
			main();
		else
			exit(0);
		break;
	}
	case 3 :
	{
		loading_screen();
		clrscr();
		cout<<"\nKruskle Algorithm (Puja part)";
		kruskal( graph , V );
		cout<<"\nDo you want to continue(1/0) : ";
		cin>>choice;
		if( choice == 1 )
			main();
		else
			exit(0);
		break;
	}

	case 4 :
	{
		loading_screen();
		clrscr();
		cout<<"\nFinal analysation ";
		cout<<"\nfor an Graph having V = 8 and E = 28 ";
		cout<<"build using adjancency matrix .";
		cout<<"\n\nfor Single pair shortest path : ";
		cout<<"\n\n\t\tDijkstra Algorithm having T.C.(V^2) = O(64)";
		cout<<"\n\tThrough this we can find the MST , all shortest path and path value";
		cout<<"\n\tThrough this we can implement Obstacle and k-path algorithm problems .";
		cout<<"\n\tWork for + edges only\n";
		cout<<"------------------------------------------------------";
		cout<<"\n\n\t\tKruskles Algorithm having T.C(Elog(V)) = O(25.2) ";
		cout<<"\n\tThrough this we can find the MST , all shortest path and path value";
		cout<<"\n\tBut having high space complexity then Dijkstras as focus is on edge here";
		cout<<"\n\tOverall better then Dijkstras for finding Single pair shortest path\n";
		cout<<"-------------------------------------------------------";
		cout<<"\n\n\t\tFloyd Warshall having T.C(V^3) = O(512)";
		cout<<"\n\tExcellent algorithm for all pair shortest path and its value ";
		cout<<"\n\tNot efficient for single source shortest path";
		cout<<"\n\tCan reduce the space complexity to O(V^3) to O(V^2)\n";		
		cout<<"\n\tWorks for both + and - edges \n";
		cout<<"--------------------------------------------------------";
		cout<<"\n\n\tSummary : ";
		cout<<"Kruskles > Dijkstras = Prims > Floyd Warhall (Single Source)";
		cout<<"\nDo you want to continue(1/0) : ";
		cin>>choice;
		if( choice == 1 )
			main();
		else
			exit(0);
		break;
	}
	case 5 :
		exit(0);
	default:
	{
		clrscr();
		cout<<"\nInvalid Choice";
		cout<<"\nDo you want to continue(1/0) : ";
		cin>>choice;
		if( choice == 1 )
			main();
		else
			exit(0);
		break;
	}

    }
    getch();
    return 0;
}

void welcome()
{
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");
	welcome_screen();
}

void welcome_screen()
{
	int a,c,v,h,g,count1,b;
	count1=380;
	for(h=1;h<=10;h++)
	{
		count1-=20;
		for(g=220;g<=count1;g++)
		{
			setcolor(h);
			circle(320,240,g);
			setcolor(15);
			circle(320,240,219);
			setfillstyle(1,h+1);
			floodfill(320,240,15);
			setcolor(0);
			settextstyle(1,0,7);
			outtextxy(150,150,"FOA Project");

	}
    }

	delay(100);
	for(a=0,c=479,b=0,v=639;a<639,c>0,b<479,v>0;a++,c--,b++,v--)
	{
		setlinestyle(0,0,0);
		setcolor(0);
		delay(10);
		line(a,0,639,c);
		line(0,b,v,479);
	}

	delay(100);

	setcolor(GREEN);
	settextstyle(7,0,6);
	outtextxy(30,100,"A PROJECT BY:-");
	outtextxy(150,180,"BURHANUDDIN");
	outtextxy(150,220,"BHOPAL");
	outtextxy(150,260,"WALA");

	settextstyle(0,0,0);
	setlinestyle(0,0,0);
	getch();
	delay(400);
	setcolor(RED);
	for(a=0,c=640;a<640,c>=0;a++,c--)
	{
		delay(2);
		line(a,0,c,480);
	}
	for(a=0,c=480;a<480,c>=0;a++,c--)
	{
		delay(2);
		line(0,a,640,c);
	}
	delay(100);
	closegraph();
}
void loading_screen()
{
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");

	int x , y ;
	cleardevice();
	x=getmaxx()/2;
	y=getmaxy()/2;
	settextstyle(TRIPLEX_FONT,HORIZ_DIR,3);
	setbkcolor(rand());
	setcolor(4);
	int c=150;
	for(int e=0;e<15;e++)
	{
		for(int i=50;i<100;i++)
		{
			settextstyle(SMALL_FONT, HORIZ_DIR, 10);
			outtextxy(x,y,"Loading...");
			settextstyle(SMALL_FONT, HORIZ_DIR, 5);
			outtextxy(x+5,y+5,"Predicting.. ");
			setcolor(3);
			circle(x,y,i);
			circle(x,y,c);
			c--;
			cleardevice();
		}
	}
	delay(10);
	closegraph();
}



