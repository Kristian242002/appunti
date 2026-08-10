import java.io.*; 
import java.net.*;

class ClientThreadREST
{    
    static int[] risultatiPrimi = new int[3];

    public static void main(String args[]) throws InterruptedException
    {
        if(args.length < 3)    {
            System.out.println("USAGE:");
            System.out.println("  java ClientThreadREST calcola-somma op1 op2 [host1 host2 host3]");
            System.out.println("  java ClientThreadREST numeri-primi min max [host1 host2 host3]");
            return;
        }

        String servizio = args[0];
        String p1 = args[1];
        String p2 = args[2];

        // Se non specificati, uso localhost per tutti e 3 (test in locale)
        String host1 = args.length > 3 ? args[3] : "127.0.0.1";
        String host2 = args.length > 4 ? args[4] : "127.0.0.1";
        String host3 = args.length > 5 ? args[5] : "127.0.0.1";

        if(servizio.equals("calcola-somma"))  {
            // Stessa operazione ripetuta su 3 server (concorrenza semplice)
            RESTAPI service1=new RESTAPI(host1, servizio, p1, p2, -1);
            RESTAPI service2=new RESTAPI(host2, servizio, p1, p2, -1);
            RESTAPI service3=new RESTAPI(host3, servizio, p1, p2, -1);

            service1.start();
            service2.start();
            service3.start();

            service1.join();
            service2.join();
            service3.join();
        }
        else if(servizio.equals("numeri-primi"))  {
            int min = Integer.parseInt(p1);
            int max = Integer.parseInt(p2);

            // Divido l'intervallo in 3 parti
            int range = max - min + 1;
            int chunk = range / 3;

            int min1 = min,      max1 = min + chunk - 1;
            int min2 = max1+1,   max2 = min2 + chunk - 1;
            int min3 = max2+1,   max3 = max; // l'ultimo prende il resto

            System.out.println("Intervallo 1 [" + min1 + "," + max1 + "] -> " + host1);
            System.out.println("Intervallo 2 [" + min2 + "," + max2 + "] -> " + host2);
            System.out.println("Intervallo 3 [" + min3 + "," + max3 + "] -> " + host3);

            long inizio = System.currentTimeMillis();

            RESTAPI service1=new RESTAPI(host1, servizio, ""+min1, ""+max1, 0);
            RESTAPI service2=new RESTAPI(host2, servizio, ""+min2, ""+max2, 1);
            RESTAPI service3=new RESTAPI(host3, servizio, ""+min3, ""+max3, 2);

            service1.start();
            service2.start();
            service3.start();

            service1.join();
            service2.join();
            service3.join();

            long fine = System.currentTimeMillis();

            int totale = risultatiPrimi[0] + risultatiPrimi[1] + risultatiPrimi[2];
            System.out.println("\nTOTALE numeri primi in [" + min + "," + max + "]: " + totale);
            System.out.println("Tempo impiegato: " + (fine - inizio) + " ms");
        }
        else    {
            System.out.println("Servizio non riconosciuto: " + servizio);
        }
    }
}

class RESTAPI extends Thread
{
    String server, service, param1, param2;
    int indice; // usato solo per numeri-primi, per sapere dove salvare il risultato

    RESTAPI(String remoteServer, String srvc, String p1, String p2, int idx)  {
        server = new String(remoteServer);
        service = new String(srvc);
        param1 = new String(p1);
        param2 = new String(p2);
        indice = idx;
    }

    public void run()   {
        if(service.equals("calcola-somma"))    {
            float ris = calcolaSomma(Float.parseFloat(param1), Float.parseFloat(param2));
            System.out.println("[" + server + "] Risultato somma: " + ris);
        }
        else if(service.equals("numeri-primi"))   {
            int ris = contaPrimi(Integer.parseInt(param1), Integer.parseInt(param2));
            System.out.println("[" + server + "] Primi trovati in [" + param1 + "," + param2 + "]: " + ris);
            ClientThreadREST.risultatiPrimi[indice] = ris;
        }
        else    {
            System.out.println("Servizio non disponibile!");
        }
    }

    synchronized float calcolaSomma(float val1, float val2)  {

        URL u = null;
        float risultato=0;
        int i;

        try 
        { 
            u = new URL("http://"+server+":8000/calcola-somma?param1="+val1+"&param2="+val2);
            System.out.println("URL aperto: " + u);
        }
        catch (MalformedURLException e) 
        {
            System.out.println("URL errato: " + u);
        }

        try 
        {
            URLConnection c = u.openConnection();
            c.connect();
            BufferedReader b = new BufferedReader(new InputStreamReader(c.getInputStream()));
            String s;
            while( (s = b.readLine()) != null ) {
                if((i = s.indexOf("somma"))!=-1)
                    risultato = Float.parseFloat(s.substring(i+7));
            }
        }
        catch (IOException e) 
        {
            System.out.println(e.getMessage());
        }
    
        return (float)risultato;
    }

    synchronized int contaPrimi(int valMin, int valMax)  {

        URL u = null;
        int risultato = 0;
        int i;

        try 
        { 
            u = new URL("http://"+server+":8000/numeri-primi?min="+valMin+"&max="+valMax);
            System.out.println("URL aperto: " + u);
        }
        catch (MalformedURLException e) 
        {
            System.out.println("URL errato: " + u);
            return 0;
        }

        try 
        {
            URLConnection c = u.openConnection();
            c.connect();
            BufferedReader b = new BufferedReader(new InputStreamReader(c.getInputStream()));
            String s;
            while( (s = b.readLine()) != null ) {
                if((i = s.indexOf("numeriPrimi"))!=-1)
                    risultato = Integer.parseInt(s.substring(i+13).trim());
            }
        }
        catch (IOException e) 
        {
            System.out.println(e.getMessage());
        }
    
        return risultato;
    }    
}
