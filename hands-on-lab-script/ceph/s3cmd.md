#### Uses of s3cmd Command Line

1. List all S3 bucket: Use the following command to list all s3 buckets in your aws account.

    ```
    $ s3cmd ls
    ```

2. Creating new bucket: To create a new bucket in Amazon s3 use the below command. It will create a bucket named **my-bucket** in S3 account.
    ```
    $ s3cmd mb s3://my-bucket
    ```


3. Uploading file in bucket: The below command will upload file **file.txt** to s3 bucket using **s3cmd** command.

    ```
    $ s3cmd put my-file.txt s3://my-bucket/
    ```

4. List Data of S3 bucket: List the objects of s3 bucket using **ls** switch with **s3cmd**.

    ```
    $ s3cmd ls s3://my-bucket/
    ```

5. Download files from bucket: Sometimes if we need to download files from the s3 bucket. Use the following commands to download it.

    ```
    $ s3cmd get s3://my-bucket/my-file.txt
    ```

6. Remove Data of S3 bucket: To remove files are folder from s3 bucket use the following commands.

    ```
    $ s3cmd del s3://my-bucket/my-file.txt
    ```

7. Remove S3 bucket: If we don’t need s3 bucket anymore, we can simply delete it using the following command.

    ```
    $ s3cmd rb s3://my-bucket
    ```

    > ![WARNING](../imgs/warning-icon.png) **WARNING**: Before removing bucket make sure its empty.
