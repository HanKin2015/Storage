git log --stat --after="2016-01-01 00:00" --before="2020-05-01 23:59" hcd-xhci.c > hcd-xhci.c.gitlog
grep commit hcd-xhci.c.gitlog | wc -l


